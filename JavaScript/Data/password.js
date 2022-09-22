new Array(16).fill().map(x => "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()<>?:\"{}"[Math.trunc(Math.random() * 79)]).join("")
String.fromCharCode(...crypto.getRandomValues(new Uint8Array(16)))
