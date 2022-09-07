(function(){
    $.extend({
        min:function(a,b){
            return a>b?b:a
        },
        max:function(a,b){
            return a>b?a:b
        },
        leftTrim:function(str){
            return str.replace(/^\s+/,'')
        },
        rightTrim:function(str){
            return str.replace(/\s+$/,'')
        }
    })

    $.fn.extend({
        checkAll:function(){
            this.prop('checked',true)
        },
        unCheckAll:function(){
            this.prop('checked',false)
        },
        reverseCheck:function(){
            //this是jQuery对象
            this.each(function(){
                //this是DOM对象
                this.checked = !this.checked
            })
        }
    })
})()