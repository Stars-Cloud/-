Function.prototype.myBind=function(context){
    // 判断调用对象是否为函数
    if(typeof this !== "function"){
        throw new Error("Error")
    }

    // 获取参数
    const args = [...arguments].slice(1),fn=this

    return function Fn(){
        return fn.apply(this instanceof Fn? new fn(...arguments):context,args.concat(arguments));
    }
}
obj = {
    name:"fan",
    sayName(){
        console.log(this.name)
    }
}
obj2 = {
    name:"xing",
    sayName(){
        console.log(this.name)
    }
}
obj.sayName.myBind(obj2)()