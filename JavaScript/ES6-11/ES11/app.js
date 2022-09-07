// import * as m1 from "./hello.js"

document.getElementsByTagName('button')[0].onclick = function(){
    import('./hello.js').then(moudle=>{
        console.log(moudle)
        moudle.hello()
    })
}