function createField(x) {
    let field = document.getElementsByClassName("field")[0]
    field.innerHTML = ""
    for(let i = 0; i < x; i++) {
        addFieldRow(field, x, i)
    }
}

function addFieldRow(field, x, y_coord) {
    let row = document.createElement("div")
    row.className = "hexagon-row"
    for(let i = 0; i < x; i++) {
        addFieldCell(row, i, y_coord)
    }
    field.appendChild(row)
}

function addFieldCell(row, x_coord, y_coord) {
    let cell = document.createElement("div")

    cell.className = "hexagon"
    cell.id = x_coord + "-" + y_coord
    cell.onclick = function() {
        OnPickHex(x_coord, y_coord)

        return false
    }

    row.appendChild(cell)
}

function renderImp(x, y, imp_type) {
    let hex = document.getElementById(x + "-" + y)
    if(imp_type == "River") {
        hex.classList.add("hexagon-imp-river")
    } else if(imp_type == "Mountains") {
        hex.classList.add("hexagon-imp-mountains")
    } else if(imp_type == "Forest") {
        hex.classList.add("hexagon-imp-forest")
    } else if(imp_type == "Swamp") {
        hex.classList.add("hexagon-imp-swamp")
    } else if(imp_type == "Rain") {
        hex.classList.add("hexagon-imp-rain")
    } else if(imp_type == "Snow") {
        hex.classList.add("hexagon-imp-snow")
    } else if(imp_type == "Fog") {
        hex.classList.add("hexagon-imp-fog")
    }
}

function setUnit(x, y) {
    let hex = document.getElementById(x + "-" + y)
    let unit = document.createElement("div")
    unit.className = "unit"
    unit.style.backgroundColor = "black";
    hex.appendChild(unit)
}

function removeUnit(x, y) {
    let hex = document.getElementById(x + "-" + y)
    hex.removeChild(hex.children[0])
}

function renderUnit(x, y, unit_type, color, style) {
    let hex = document.getElementById(x + "-" + y)
    let unit = document.createElement("div")
    unit.style.backgroundColor = color;

    if(unit_type == "Archer") {
        unit.classList.add("hexagon-unit-archer")
    } else if(unit_type == "Tank") {
        unit.classList.add("hexagon-unit-tank")
    } else if(unit_type == "Knight") {
        unit.classList.add("hexagon-unit-knight")
    } else if(unit_type == "King") {
        unit.classList.add("hexagon-unit-king")
    } else if(unit_type == "Priest") {
        unit.classList.add("hexagon-unit-priest")
    } else if(unit_type == "Killer") {
        unit.classList.add("hexagon-unit-killer")
    } else {
        unit.classList.add("hexagon-unit-own" + style)
    }

    
    hex.appendChild(unit)
}

function makeReachable(x, y) {
    let hex = document.getElementById(x + "-" + y)
    hex.classList.add("hexagon-picked")
}

function showHexInfo(x, y, unit_name, imp_name) {
    let hex = document.getElementById("picked-hex-info")
    let coord = document.getElementById("picked-hex-info-coord")
    let unit = document.getElementById("picked-hex-info-unit")
    let imp = document.getElementById("picked-hex-info-imp")


    hex.style.display = "flex"

    coord.textContent = "Coord: (" + x + ", " + y + ")"
    unit.textContent = "Unit: " + unit_name
    imp.textContent = "Impediment: " + imp_name
}

function setLogMode(mode) {
    let hex = document.getElementById("log-mode")

    if(mode == 1) {
        hex.textContent = "Log mode: On(no cache)"
    } else if(mode == 2) {
        hex.textContent = "Log mode: Cached"
    } else if(mode == 3) {
        hex.textContent = "Log mode: Off"
    }
}

function showNextTurn(player_name, turn) {
    let player = document.getElementById("current-turn-player")
    let num_of_moves = document.getElementById("num-of-moves-info")

    player.textContent = "Current turn: " + player_name
    num_of_moves.textContent = "Number of moves: " + turn
}

function showPickedUnit(attack, range, health, health_max, energy, energy_max) {
    let unit_info = document.getElementById("picked-unit-info")

    unit_info.style.display = "flex"

    let attack_el = document.getElementById("unit-attack")
    let range_el = document.getElementById("unit-attack-range")
    let health_el = document.getElementById("unit-health")
    let energy_el = document.getElementById("unit-energy")

    attack_el.textContent = "Attack: " + attack
    range_el.textContent = "Attack range: " + range
    health_el.textContent = "Health: " + health + "/" + health_max
    energy_el.textContent = "Energy: " + energy + "/" + energy_max
}

function newGame() {
    let next = document.getElementById("next-btn")
    let cub = document.getElementById("create-unit-btn")

    cub.disabled = false
    next.disabled = false
}

function endGame() {
    let next = document.getElementById("next-btn")
    let cub = document.getElementById("create-unit-btn")

    cub.disabled = true
    next.disabled = true
}

function printLogs(str) {
    let logs = document.getElementById("logs")
    logs.style.display = "block"
    logs.innerHTML = str;
    logs.scrollTo(0, logs.scrollHeight + 100)
}

function showCreateUnitModal() {
    let modal = document.getElementById("create-unit-modal")

    modal.style.display = "flex"

    let udu = document.getElementById("create-userdef-unit")

    udu.innerHTML = "<h1>User defined units</h1>"
}

function addUserDefineUnit(index, name) {
    let udu = document.getElementById("create-userdef-unit")
    let btn = document.createElement("button")

    btn.classList.add("btn")
    btn.onclick = function() {
        OnCreateNewUnit(index)
    }
    btn.innerHTML = name

    udu.append(btn)
}

function closeCreateUnitModal() {
    let modal = document.getElementById("create-unit-modal")

    modal.style.display = "none"
}


function pickCell(x, y) {
    let hex = document.getElementById(x + "-" + y)
    let player = document.getElementById("current-turn-player")


    hex.style.backgroundColor = "#6300a0"
}

hexagon_style_picked = 1
function hexCreateUnitStyle(index) {
    let style = document.getElementsByClassName("hex-style-crt")

    style[hexagon_style_picked - 1].classList.remove("hexagon-picked")

    hexagon_style_picked = index

    style[hexagon_style_picked - 1].classList.add("hexagon-picked")
}

function createOwnUnit() {
    let unit_type = document.getElementsByName("unit_type")[0].value;
    let attack = document.getElementsByName("attack")[0].value;
    let range = document.getElementsByName("range")[0].value;
    let armor = document.getElementsByName("armor")[0].value;
    let health = document.getElementsByName("health")[0].value;
    let energy = document.getElementsByName("energy")[0].value;
    let style = hexagon_style_picked

    let imp = document.getElementById("picked-hex-info-imp")

    if(!unit_type) return

    OnCreateNewUnit(unit_type, attack, range, armor, health, energy, style);
}