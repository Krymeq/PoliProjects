$(document).ready(() => {
    const getData = url => 
    {
        return new Promise((resolve, reject) => {
            let request = new XMLHttpRequest();
            request.open('GET', url, true);
            request.onload = () => {
                if(request.status == 200)
                    resolve(request.response);
                else
                    reject(request);
            }
            request.send();
        })
    }
    
    const mapResponseToHTML = response => {
        for(let person of response.data){
            $(`#content`).append(`<tr><td>${person.first_name}</td><td>${person.last_name}</td><td>${person.email}</td></tr>`);
        }
    }

    $(`#request`).one('click', () => 
    getData(`https://reqres.in/api/users?per_page=10`)
        .then(resp => mapResponseToHTML(JSON.parse(resp))));
});