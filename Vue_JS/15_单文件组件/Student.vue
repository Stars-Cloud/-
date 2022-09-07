<template>
    <div>
        <h2>student-name:{{studentName}}</h2>
        <h2>student-age:{{age}}</h2>
    </div>
</template>

<script>
    export default{
        // eslint-disable-next-line vue/multi-word-component-names
        name:"Student",
        data() {
            return {
                studentName: 'Fan',
                age:21,
            }
        },
    }
</script>

<style>

</style>