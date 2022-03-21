import React, { useState, useEffect } from "react";
import io from "socket.io-client";
import Input from "./Input"

const socket = io("http://localhost:8080");

export default function App() {
  const [messages, setMessages] = useState([]);
  const [loggedIn, isLoggedIn] = useState(false);
  const [loggedUsers, setLoggedUsers] = useState([]);

  useEffect(() => {
    socket.on('message', data => {
      setMessages(m => [...m, data]);
    });

    socket.on('login', (users, username) => {
      console.log(`hello ${username}`);
      setMessages(m => [...m, `${username} has joined the chat!`]);
      setLoggedUsers(users)
    });

    socket.on('logout', user => {
      setMessages(m => [...m, `${user.username} has disconnected`]);
      setLoggedUsers(users => users.filter(e => e.id !== user.id))
    });
  }, []);

  const send = (message) => {
    socket.emit('message', message);
  }

  const login = (username) => {
    socket.emit('login', username)
    isLoggedIn(true);
  }
  
  return (
    <div className="main">
    { !loggedIn ? 
    <div>
      <h1>LOG IN:</h1>
      <Input send={login} buttonText="Login"/>
    </div>
    : 
      <div className = "chat-container">
        <div className = "logged-users">
          <h4>Logged users:</h4>
          {loggedUsers.map(e => <span>{e.username}</span>)}
        </div>
        <div className = "messages">
          {messages.map((m, index) => <div className="message" key={index}>{m}</div>)}
        </div>
        <Input send={send} buttonText='Send' />
      </div>}
    </div>
  );
}