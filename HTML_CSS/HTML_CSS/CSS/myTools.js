/*
    参数：
        obj： 要添加的对象
        cn：要添加的className
*/
function addClass(obj, cn){
    if(!hasClass(obj, cn)){
        obj.className += " "+cn;
    }
    
}
/*
    判断一个元素中是否含有指定的class属性值
    如果有该class，则返回true，
*/
function hasClass(obj, cn){
    // let reg = /\bb2\b/;
    let reg = new RegExp("\\b"+cn+"\\b");
    return reg.test(obj.className);
}
/*
    删除一个指定的类
*/
function removeClass(obj, cn){
    let reg = new RegExp("\\b"+cn+"\\b");
    obj.className = obj.className.replace(reg, "");
}
/*
    toggleClass 可以用来切换一个类
    如果元素中具有该类，则删除
    如果元素中没有该类，则删除
*/
function toggleClass(obj, cn){
    if(hasClass(obj,cn)){
        removeClass(obj, cn);
    }
    else{
        addClass(obj, cn);
    }
}