var CHUNKS_LENGTH = 400;

var localStorage = window.localStorage

var send = function (queue){

	var index = 0;
	var retries = 0;

	var doo = function(){

		if (queue[index]){
		
			console.log('sending '+JSON.stringify(queue[index]))
			Pebble.sendAppMessage(queue[index], success, fail)
		}
	}

	var success = function(){

		console.log('Packet sent')
		index += 1
		retries = 0
		doo()

	}
	var fail = function (){

		retries += 1
		if (retries == 3){

			console.log('Packet fails, moving on')
			index += 1
		}
		doo()
	}

	doo()
}

var sendMemo = function (){

	var a = localStorage.getItem('text')
	if (a){

		var chunks = Math.ceil(a.length/CHUNKS_LENGTH)
		var queue = []
		
		for (var i = 0; i < chunks; i++){

			var payload = {resource:0, text:a.substring(CHUNKS_LENGTH*i, CHUNKS_LENGTH*(i+1))}
			if (i == 0) payload.start = "yes"
			if (i == chunks-1) payload.end = "yes"


			queue.push(payload)
		}

		send(queue)
	}

}
Pebble.addEventListener("ready", function (e){

	sendMemo();
})

Pebble.addEventListener("showConfiguration", function (e){

	var v = {}
	var a = localStorage.getItem('text')
	if (a) v.text = a

	Pebble.openURL("http://izqui.me/html/chebble.html?"+encodeURIComponent(JSON.stringify(v)))
})

Pebble.addEventListener("webviewclosed", function(e){

	console.log(e.response)
	if (e.response){

		var json = JSON.parse(e.response)
		if (json.text){

			localStorage.setItem("text", json.text)
			sendMemo();
		}
	}
})