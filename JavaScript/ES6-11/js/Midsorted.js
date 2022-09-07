(function(window){
    const Midsort =  function(tar,...args){
        let first = 0
        let last = args.length-1
        let found = false
        let i = 0
        // debugger
        while(first <= last && !found){
            let mid = Math.floor((last+first) / 2)
            if(tar === args[mid]){
                found = true
            }else{
                if(tar > args[mid]){
                    first = mid + 1
                }
                else{
                    last = mid - 1
                }
            }
        }
        return found
    }
    const hash =  function(astring, tablesize){
        let sum = 0
        for(let index in astring){
            for(let char of astring)
            sum = sum + char.charCodeAt(0)*index
        }
        return sum % tablesize
    }
    window.Midsort = Midsort
    window.hash = hash
})(window)