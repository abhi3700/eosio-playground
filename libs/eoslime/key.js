const eoslime = require('eoslime');

const name = eoslime.utils.nameFromPrivateKey('private key');
name.then(function(result) {
	console.log("Name: " + name.toString());
})
// console.log("Name %s", (name).toString());