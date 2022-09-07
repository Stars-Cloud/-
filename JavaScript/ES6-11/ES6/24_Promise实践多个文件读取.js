// 引入 fs 模块
    const fs = require('fs')

    /*fs.readFile('./为学.md',(err,data1)=>{
        fs.readFile('./插秧诗',(err,data2)=>{
            fs.readFile('./观书有感',(err,data3)=>{
                let result =  data1+'\n'+data2+'\n'+data3
                console.log(result)
            })
        })
    })*/

    const p = new Promise((resolve,reject)=>{
        fs.readFile('./为学.md',(err,data)=>{
            resolve(data)
        })
    })

    p.then(value=>{
        return new Promise((resolve,reject)=>{
            fs.readFile('./插秧诗.md',(err,data)=>{
                resolve([value,data])
            })
        })
    }).then(value => {
        return new Promise((resolve,reject)=>{
            fs.readFile('./观书有感.md',(err,data)=>{
                value.push(data)
                resolve(value)
            })
        })
    }).then(value=>{
        console.log(value.join('\n'))
    })
