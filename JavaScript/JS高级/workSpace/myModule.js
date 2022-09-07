// function myModule(){
//     // 私有数据
//     let msg = 'my name'
//     // 操作数据的函数
//     function doSomething(){
//         console.log('doSomething()'+msg.toUpperCase())
//     }
//     function doOtherThing() {
//         console.log('doOtherThing()'+msg.toLowerCase())
//     }
//     // 向外暴露对象（给外部使用的方法）
//     return {
//         doSomething:doSomething,
//         doOtherThing:doOtherThing
//     }
// }
(function(){
    // 私有数据
    let msg = 'my name'
    // 操作数据的函数
    function doSomething(){
        console.log('doSomething()'+msg.toUpperCase())
    }
    function doOtherThing() {
        console.log('doOtherThing()'+msg.toLowerCase())
    }

    window.myModule = {
        doSomething:doSomething,
        doOtherThing:doOtherThing
    }

})()