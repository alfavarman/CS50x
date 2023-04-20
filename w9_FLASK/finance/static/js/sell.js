
const symbolSelect = document.getElementById("symbol");
const quantityContainer = document.getElementById("quantity-container");
const sharesInput = document.getElementById("shares");

symbolSelect.onchange = function() {
    const selectedOption = symbolSelect.options[symbolSelect.selectedIndex];
    const positionQuantity = selectedOption.dataset.position;
    sharesInput.value = "";
    quantityContainer.innerHTML = `
        <label for="shares">Quantity of shares to sell (available: ${positionQuantity}):</label>
        <input autocomplete="on" autofocus class="form-control mx-auto w-auto" required="true" id="shares" name="shares" placeholder="Quantity" type="number" min="1" max="${positionQuantity}">
    `;
};
