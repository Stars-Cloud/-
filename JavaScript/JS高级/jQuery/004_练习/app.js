/*
    功能说明：
        1.点击向右（向左）的图标，平滑切换到下（上）一页
        2.无线循环切换：第一页的上一页为最后页，最后一页的下一页是第一页
        3.每隔3s自动滑动到下一页
        4.当鼠标进入图片区域时，自动切换停止，当鼠标离开后，又开始自动切换
        5.切换页面时，下面的圆点也同步更新
        6.点击圆点图标切换到对应的页
*/
$(function(){
    let $container = $('#container')
    let $list = $('#list')
    let $points = $('#pointsDiv>span')
    let $prev = $('#prev')
    let $next = $('#next')
    const PAGE_WIDTH = 600
    const TIME= 400
    const ITEM_TIME = 20
    let imgCount = $points.length

    console.log(imgCount)
    $next.click(function(){
        nextPage(true)
    })
    $prev.click(function(){
        nextPage(false)
    })

    /*
        平滑翻页
        @param next
        true：下一页
        false：上一页
    */
    function nextPage(next){
        /*
            总的时间：TIME = 400
            单元移动的间隔时间：ITEM_TIME = 20
            总的偏移量：offset
            单元移动的偏移量：itemOffset = offset/(TIME/ITEM_TIME)

            启动循环定时器不断更新$list的left，到达目标处停止定时器
        */
        let offset = 0
        offset = next?-PAGE_WIDTH:PAGE_WIDTH
        let itemOffset = offset/(TIME/ITEM_TIME)
        let currLeft = $list.position().left
        let targetLeft = currLeft + offset

        let intervalID = setInterval(function(){
            // console.log($list.position().left)
            currLeft = currLeft + itemOffset

            if(currLeft === targetLeft){
                clearInterval(intervalID)
                if(currLeft === -(imgCount+1)*PAGE_WIDTH){
                    currLeft = -PAGE_WIDTH
                }
                else if(currLeft === 0){
                    currLeft = -imgCount*PAGE_WIDTH
                }
            }
            
            $list.css('left', currLeft)

        },ITEM_TIME)
    }
})