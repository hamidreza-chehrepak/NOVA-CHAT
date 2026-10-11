
const express = require("express");
const http = require("http");
const { Server } = require("socket.io");
const path = require("path");

const app = express();
const server = http.createServer(app);
const io = new Server(server);

const PORT = process.env.PORT || 10000;

app.use(express.static(__dirname));

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "index.html"));
});

io.on("connection", (socket) => {
  console.log("A user connected:", socket.id);

  socket.on("chat message", (data) => {
    if (!data || typeof data.name !== "string" || typeof data.text !== "string") {
      return;
    }

    const name = data.name.trim().slice(0, 30);
    const text = data.text.trim().slice(0, 1000);

    if (!name || !text) return;

    io.emit("chat message", { name, text });
  });

  socket.on("disconnect", () => {
    console.log("A user disconnected:", socket.id);
  });
});

server.listen(PORT, "0.0.0.0", () => {
  console.log("NOVA-CHAT running on port " + PORT);
});
