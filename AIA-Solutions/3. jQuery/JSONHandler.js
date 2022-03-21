$(document).ready(() => {
    $(`#loader`).click(() => {
        $.getJSON(`guitars.json`, (data) => {
            for(let guitar of data.Guitars.Guitar){
                $(`#content`).append(`<tr><td>${guitar.Brand}</td><td>${guitar.Model}</td>`);
            }
        });
    })

});