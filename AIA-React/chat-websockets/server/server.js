const io = require("socket.io");
const server = io.listen(8080);
let users = []

server.on('connection', (socket) => {
    socket.on('message', (message) => {
        const sender = users.find(e => e.id === socket.id);
        console.log(`New message: ${message}`);
        server.emit('message', `${sender.username}: ${message}`);
    });

    socket.on('login', (username) => {
        const newUser = {id: socket.id, username};
        console.log(`${username} has logged in`);
        users.push(newUser);
        server.emit('login', users, username)
    })

    socket.on("disconnect", () => {
        const user = users.find(e => e.id === socket.id)
        users = users.filter(e => e.id !== socket.id)
        console.log(`${user.username} has disconnected`);
        server.emit('logout', user)
    })
});