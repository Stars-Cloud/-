//1.引入 fs 模块
const fs = require('fs');

//2.调用方法读取文件
/*
fs.readFile('./为学.md',(err,data)=>{
    if(err) throw err;
    console.log(data.toString())
})
*/

let text = new Promise(function(resolve,reject){
    fs.readFile('./为学.md',(err,data)=>{
        if(err) reject(err)
        resolve(data)
    })
})

text.then(function(value){
    console.log(value.toString())
},function(reason){
    console.log(reason)
})