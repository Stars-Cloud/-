// 1. 引入express
const express = require('express')

// 2.创建应用对象
const app = express()

// 2.创建路由规则
// request 是对请求报文的封装
// response 是对响应报文的封装
app.get('/server',(request,response)=>{
    // 设置响应头 设置允许跨域
    response.setHeader("Access-Control-Allow-Origin","*")
    console.log(request.username)
    // 设置响应体
    response.send('HELLO EXPRESS get')
})

app.post('/server',(request,response)=>{
    // 设置响应头 设置允许跨域
    response.setHeader("Access-Control-Allow-Origin","*")
    // 设置所有的请求头都可以接收
    response.setHeader('Access-Control-Allow-Headers','*')
    // 设置响应体
    response.send('HELLO EXPRESS post')
})

// app.all 表示http的所有的请求都可接收
app.all('/json-server',(request,response)=>{
    // 设置响应头 设置允许跨域
    response.setHeader("Access-Control-Allow-Origin","*")
    // 设置所有的请求头都可以接收
    response.setHeader('Access-Control-Allow-Headers','*')
    // 设置响应体
    const data = {
        name:'atguigu',
        age:21
    }
    // send的参数：字符串/buffer 类型
    // 对对象进行字符串的转换
    let str = JSON.stringify(data)
    response.send(str)
})

app.all('/timeout',(request,response)=>{
    // 设置响应头 设置允许跨域
    response.setHeader("Access-Control-Allow-Origin","*")
    // 设置所有的请求头都可以接收
    response.setHeader('Access-Control-Allow-Headers','*')
    // 设置响应体
    setTimeout(()=>{
        response.send('延时响应')
    },3000)
})

// jQuery
app.all('/jQuery-server',(request,response)=>{
    // 设置响应头 设置允许跨域
    response.setHeader("Access-Control-Allow-Origin","*")
    // 设置所有的请求头都可以接收
    response.setHeader('Access-Control-Allow-Headers','*')
    // 设置响应体
    const data = {name:'Fan'}
    setTimeout(()=>{
        response.send(JSON.stringify(data))
    },1000)
})

// axios
app.all('/axios-server',(request,response)=>{
    // 设置响应头 设置允许跨域
    response.setHeader("Access-Control-Allow-Origin","*")
    // 设置所有的请求头都可以接收
    response.setHeader('Access-Control-Allow-Headers','*')
    // 设置响应体
    const data = {name:'Fan'}
    setTimeout(()=>{
        response.send(JSON.stringify(data))
    },1000)
})

// fetch
app.all('/fetch-server',(request,response)=>{
    // 设置响应头 设置允许跨域
    response.setHeader("Access-Control-Allow-Origin","*")
    // 设置所有的请求头都可以接收
    response.setHeader('Access-Control-Allow-Headers','*')
    // 设置响应体
    const data = {name:'Fan'}
    setTimeout(()=>{
        response.send(JSON.stringify(data))
    },1000)
})

// jsonp
app.all('/jsonp-server',(request,response)=>{
    // response.send("console.log('hello jsonp')")
    const data = {
        name:'fanxingtong'
    }
    let str = JSON.stringify(data)
    response.end(`handel(${str})`)
})

// username
app.all('/check-username',(request,response)=>{
    const data = {
        exit:1,
        msg:'该用户名已使用'
    }
    let str = JSON.stringify(data)
    response.send(`handel(${str})`)
})

// jquery-jsonp
app.all('/jquery-jsonp',(request,response)=>{
    const data = {
        name:'樊星彤',
        age:21
    }
    let str = JSON.stringify(data)
    const cd = request.query.callback

    response.end(`${cd}(${str})`)
})

// cors-server
app.all('/cors-server',(request,response)=>{
    // 设置响应头
    response.setHeader('Access-Control-Allow-Origin','*')
    // response.setHeader('Access-Control-Max-Age','true')
    response.setHeader('Access-Control-Allow-Headers','*')
    // 各种请求方法都可使用 get put post delete
    response.setHeader('Access-Control-Allow-Method','*')
    response.send('hello')
})




app.get('/ES8-async-await',(request,response)=>{
    response.setHeader('Access-Control-Allow-Origin','*')
    let person = {
        name:"fan",
        age:21
    }
    let data = JSON.stringify(person)
    response.send(data)
})
// 4. 监听端口启动服务
app.listen(8000,()=>{
    console.log('服务已经启动,8000 端口监听中.....')
})


/*
const xhr = XMLHttpRequest()
xhr.open('GET',"http://127.0.0.1:8000/server")
xhr.send()
xhr.onreadystatechange = function(){
    if(xhr.readyState === 4){
        if(xhr.status >= 200 && xhr.status < 300){
            console.log(xhr.respond)
        }else{
            console.log(xhr.status)
        }
    }
}
*/
