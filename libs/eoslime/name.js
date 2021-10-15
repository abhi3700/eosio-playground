const eoslime = require('eoslime');

// a promise pending funciton
const randomName = eoslime.utils.randomName();
randomName.then(function(result){
	console.log("Random name: " + result);		// => lfb3a45e344e
})


// const name = eoslime.utils.nameFromPrivateKey('private key');
// console.log("Name %s", (name).toString());