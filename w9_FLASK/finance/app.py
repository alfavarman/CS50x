import os
import datetime
import re
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, Blueprint
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# for debugging purpuses comment above line and use below one
# db = SQL("sqlite:///w9_flask/finance/finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    data = db.execute(
        "SELECT ticker, SUM(CASE WHEN position = 'B' THEN quantity ELSE -quantity END) as position_quantity, AVG(price) as average_price FROM portfolio WHERE user_id = ? GROUP BY ticker",
        (user_id,),
    )
    account_summary = 0
    for row in data:
        row["current_price"] = round((lookup(row["ticker"])["price"]), 2)
        row["market_value"] = round(
            (int(row["position_quantity"]) * row["current_price"]), 2
        )
        account_summary += row["market_value"]

    balance = db.execute("SELECT cash FROM users WHERE id = ?", (user_id,))[0]["cash"]
    account_summary += balance

    return render_template(
        "index.html", portfolio=data, account_summary=account_summary, balance=balance
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # buy ticket
        quantity = request.form.get("shares")
        ticker = request.form.get("symbol")

        # if user supply ticker
        if ticker:
            # if user supply quantity and its positive int
            if quantity and quantity.isdigit() and int(quantity) > 0:
                quantity = int(quantity)
            else:
                return apology("hey m8, but how much ???", 400)

            values = lookup(ticker)
            # If ticker was found
            if values:
                price = values["price"]

                amount = price * quantity

                # if user can afford
                user_id = session["user_id"]
                available = db.execute("SELECT cash FROM users WHERE id=?", user_id)[
                    0
                ]["cash"]
                balance = available - amount

                if balance < 0:
                    return apology(
                        "insufficient balance to complete operation, try lower quantity",
                        400,
                    )
                else:
                    # get user datetime
                    date_time = datetime.datetime.now()

                    # format to fit db table
                    date = date_time.strftime("%Y-%m-%d")
                    time = date_time.strftime("%H:%M:%S")

                    # insert into table portfolio : date , time, quantity, price, transaction type, ticker
                    db.execute(
                        "INSERT INTO portfolio (user_id, ticker, quantity, position, price, date, time) VALUES (?, ?, ?, ?, ?, ?, ?)",
                        user_id,
                        ticker,
                        quantity,
                        "B",
                        price,
                        date,
                        time,
                    )

                    # update into users cash -= amount
                    db.execute(
                        "UPDATE users SET cash = cash - ? WHERE id = ?", amount, user_id
                    )

                    # message:
                    flash(
                        f"Your order BUY {amount} of {ticker} at {usd(price)} was successful"
                    )

                    # TODO log event

                    # redirect to portfolio
                    return redirect("/")

            else:
                return apology("ticker not found, verify and try again", 400)
        else:
            return apology("provide stock ticker", 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("/buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions only GET method allowed"""

    user_id = session.get("user_id")
    data = db.execute("SELECT ticker, quantity, position, price, date, time FROM portfolio WHERE user_id=?", user_id)

    return render_template("/history.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # form for quote
    if request.method == "GET":
        return render_template("quote.html")

    # get quote
    if request.method == "POST":
        ticker = request.form.get("symbol")
        if ticker:
            values = lookup(ticker)
            if values:
                return render_template("quote.html", values=values)

    return apology("ticker not found. verify ticker and try again")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # redirect logged users to home
    if session.get("user_id"):
        return redirect("/")

    # registering
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # User not taken
        username = request.form.get("username")
        username_taken = db.execute(
            "SELECT username FROM users WHERE username=?", username
        )
        if username_taken:
            return apology("username taken, choose other", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        password = str(request.form.get("password"))
        if not re.match("^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$", password):
            return apology("follow password instructions", 400)

        # Ensure password was submitted
        if (not request.form.get("confirmation")
                or request.form.get("confirmation") != password):
            return apology("must repeat same password", 400)

        hash = generate_password_hash(str(request.form.get("password")))
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # message:
        flash("Registration successful. Please Log In")

        return redirect("/login")

    if request.method == "GET":
        return render_template("register.html")

    # if any
    return apology("Registration Error, Report to admin", 400)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    # get users positions, total amount
    portfolio = db.execute(
        "SELECT ticker, SUM(CASE WHEN position = 'B' THEN quantity ELSE -quantity END) as position_quantity FROM portfolio WHERE user_id = ? GROUP BY ticker",
        (user_id,),
    )

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # sell ticket
        ticker = request.form.get("symbol")
        if not ticker:
            return apology("select from positions you own", 400)

        quantity = int(request.form.get("shares"))

        if not quantity:
            return apology("available quantity", 400)

        # find position in portfolio
        for position in portfolio:
            # if user own stock and quantity
            if (
                position["ticker"] == ticker
                and quantity <= position["position_quantity"]
            ):
                # realtime price
                current_price = lookup(ticker)["price"]
                amount = current_price * quantity

                # get user datetime
                date_time = datetime.datetime.now()
                # format to fit db table
                date = date_time.strftime("%Y-%m-%d")
                time = date_time.strftime("%H:%M:%S")

                # sell stock add cash to balance
                db.execute(
                    "INSERT INTO portfolio (user_id, ticker, quantity, position, price, date, time) VALUES (?, ?, ?, ?, ?, ?, ?)",
                    user_id,
                    ticker,
                    quantity,
                    "S",
                    current_price,
                    date,
                    time,
                )
                # update balance
                db.execute(
                    "UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id
                )
                # TODO logger

                # flash "ticket SELL successful"
                flash("SELL ticket successful")

                # redirect index
                return redirect("/")
            else:
                # You dont have enough stock.
                return apology("Short Sell not allowed, sell owned quantity", 400)
    # "GET"
    else:
        return render_template("sell.html", portfolio=portfolio)
