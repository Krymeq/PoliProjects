const table = document.getElementById('collection');
const newRows = document.getElementById('pending')
const Guitar = (make, model) => ({make, model});

let content = [
    Guitar("Fender", "Stratocaster"),
    Guitar("Gibson", "Les Paul"),
    Guitar("Schecter", "ZV Mirror"),
    Guitar("Ibanez", "RG2137")
];

const mapGuitarsToHTML = (guitars) => {
    let nextId = 1;
    let html = "";
    for(let guitar of guitars){
        html += 
        `<div class = "table-row" id = ${nextId}>
            <span>${nextId}</span>
            <span>${guitar.make}</span>
            <span>${guitar.model}</span>
            <button>
                <span>
                    Edit
                </span>
            </button>
            <button>
                <span>
                    Remove
                </span>
            </button>
        </div>`
        nextId++;
    }

    table.innerHTML = html;
}

mapGuitarsToHTML(content);