let Hello= require('./hello')
hello = new Hello()
hello.setName('Fan')
hello.sayHello()

let obj = {}
let obj2 = new Object()
console.log(Object.prototype.toString.call(obj),Object.prototype.toString.call(obj2))