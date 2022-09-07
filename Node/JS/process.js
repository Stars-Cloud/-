// import process from 'node:process'

/*let a =1;
setTimeout(()=>{
    console.log(a)
},100)

a = 2
setTimeout(()=>{
    console.log(a)
},100)

a = 3*/


class A {
    constructor() {
        console.log(new.target.name);
    }
}

class B extends A { constructor() { super(); } }

var a = new A(); // logs "A"
var b = new B(); // logs "B"

class C { constructor() { console.log(new.target); } }
class D extends C { constructor() { super(); } }

var c = new C(); // logs class C{constructor(){console.log(new.target);}}
var d = new D(); // logs class D extends C{constructor(){super();}}
