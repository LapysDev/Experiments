new Array(16).fill().map(x => "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()<>?:\"{}".charAt(Math.trunc(Math.random() * 79))).join("")
Array.from(crypto.getRandomValues(new Uint8Array(16))).map(x => "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()<>?:\"{}".charAt(x % 79)).join("")
