const btn = document.querySelector('button')
const h = document.querySelector('h1')

function setUserName(){
    let userName = prompt('请输入你的名字：')
    localStorage.setItem('name',userName)
    h.textContent = 'Hello'+userName
}
export {btn,h,setUserName}