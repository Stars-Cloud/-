function feiBoNaQie(n){
    return n<=2?1:feiBoNaQie(n-1)+feiBoNaQie(n-2)
}
console.log(this)
onmessage = function(event){
    let number = event.data
    console.log('分线程接受到主线程发送的数据：'+number)
    // 计算
    let result = feiBoNaQie(number)

    console.log('分线程向主线程返回数据'+result)
    postMessage(result)
    // 分线程中的全局对象不再是window，所以在分线程中不能更新界面
}