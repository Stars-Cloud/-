const fs =require('fs')

function readWeiXue(){
    return new Promise((resolve,reject)=>{
        fs.readFile("../为学.md",(err,data)=>{
            // if fail
            if(err) reject(err)
            // if success
            resolve(data)
        })
    })
}

function readChaYangShi(){
    return new Promise((resolve,reject)=>{
        fs.readFile("../插秧诗.md",(err,data)=>{
            // if fail
            if(err) reject(err)
            // if success
            resolve(data)
        })
    })
}

function readGuanShuYouGan(){
    return new Promise((resolve,reject)=>{
        fs.readFile("../观书有感.md",(err,data)=>{
            // if fail
            if(err) reject(err)
            // if success
            resolve(data)
        })
    })
}

// 声明一个 async 函数
async function　main(){
    let weixue = await readWeiXue()
    let chayang = await readChaYangShi()
    let guanshu = await readGuanShuYouGan()

    console.log(weixue.toString())
    console.log(chayang.toString())
    console.log(guanshu.toString())
}
main()