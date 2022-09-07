<template>
<!--    组件的结构-->
    <div class="box">
        <h2>school-name:{{schoolName}}</h2>
        <h2>school-address:{{schoolAddress}}</h2>
        <button @click="showInfo">click show schoolName</button>
    </div>
</template>

<script>
    // 组件交互相关的代码（数据、方法等）
    // eslint-disable-next-line no-undef
    export default Vue.extend({
        // eslint-disable-next-line vue/multi-word-component-names
        name:'School',
        data(){
            return {
                schoolName:"xike",
                schoolAddress:"xian",
            }
        },
        methods:{
            showInfo(){
                alert(this.schoolName)
            }
        },
    })
</script>

<style>
    /*组件的样式*/
    .box{
        width: 500px;
        height: 500px;
        background: aquamarine;
    }
</style>