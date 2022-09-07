// 1.点击向右（向左）的图标，平滑切换到下（上）一页

let $list = $('#list')
let $prev = $('#prev')
let $next = $('#next')
let $points = $('#pointsDiv>span')
const OFFSET = 600
const ITEM_OFFSET = 6
let imgCount = $('#list>img:not(:first,:last)').length
// console.log(imgCount)
// $points.filter(':first').css('backgroundColor','skyblue')

$prev.click(function(){
    nextPicture(false)
})

$next.click(function(){
    nextPicture(true)
})

function nextPicture(next){
    let currentOffset = $list.position().left // 获取当前的偏移量
    let target = currentOffset + (next?-OFFSET:OFFSET) // 目标偏移量
    let intervalID = setInterval(function(){
        currentOffset = currentOffset+(next?-ITEM_OFFSET:ITEM_OFFSET) // 循环定时器每一次调用都更新当前的偏移量

        if(currentOffset === target){
            clearInterval(intervalID)
            if(currentOffset === -(imgCount+1)*OFFSET){
                currentOffset = -OFFSET
            }
            else if(currentOffset === 0){
                currentOffset = -imgCount*OFFSET
            }
        }

        $list.css('left', currentOffset)
    },10)
    /*
        总距离 600
        每隔10毫秒定时器工作一次，每一次使图片偏移6px
        600/6==100 即需要调用60次定时器
        总共需要 100*10 = 1000 毫秒
    */
}
