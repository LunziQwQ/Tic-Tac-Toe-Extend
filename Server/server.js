/**
 * Created by XX on 2016/6/5.
 */

var net=require('net');

var server = net.createServer();

var sockets=[];

var gaming=[];

server.on('connection',function (socket) {
	console.log('got a new connection');

	socket.net_code=0;

	sockets.push(socket);
	
	socket.on('data',function (data) {

		console.log('got data:',data);

		if(data.indexOf("code:")!==-1){

			var temp ='';

			var index = -1;

			temp+=data;

			temp=temp.substring(5);

			for (var i=0;i<gaming.length;i++){
				if (gaming[i] == temp){
					index = i;
					break;
				}
			}

			if (index == -1){

				sockets.forEach(function (otherSocket) {
					if (otherSocket !== socket && otherSocket.net_code == socket.net_code){
						otherSocket.write("error:your opponent is die");
					}
				});
				var index1=gaming.indexOf(socket.net_code);
				gaming.splice(index1,1);

				socket.net_code=temp;

				sockets.forEach(function (otherSocket) {
					if (otherSocket !== socket && otherSocket.net_code == socket.net_code){
						otherSocket.write("red");
						socket.write("blue");
						gaming.push(socket.net_code);
					}
				});
			}else{
				socket.write("You can't use the code");
			}
		} else {
			sockets.forEach(function (otherSocket) {
				if (otherSocket !== socket && otherSocket.net_code == socket.net_code){
					otherSocket.write(data);
				}
			});
		}
	});
	
	socket.on('close',function () {
		console.log('connection closed');
		sockets.forEach(function (otherSocket) {
			if (otherSocket !== socket && otherSocket.net_code == socket.net_code){
				otherSocket.write("error:your opponent is die");
			}
		});
		var index1=gaming.indexOf(socket.net_code);
		gaming.splice(index,1);
		var index=sockets.indexOf(socket);
		sockets.splice(index,1);
	});

	socket.on('error',function (err) {
		console.log("error:",err.message);
	});
});

server.on('error',function (err) {
	console.log('Server error:',err.message);
});

server.on('close',function () {
	console.log('Server closed');
});

server.listen(4001);