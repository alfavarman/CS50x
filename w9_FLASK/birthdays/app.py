import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name, month, day = None, None, None

        # simple input validation before assign variables
        if str(request.form.get("name")).isalpha():
            name = request.form.get("name")

        if int(request.form.get("month")) in range(1,13):
            month = request.form.get("month")

        if int(request.form.get("day")) in range(1,32):
            day = request.form.get("day")


        # db operation if variables are not None
        if name and month and day:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (%s, %s, %s)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdates = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdates=birthdates)


