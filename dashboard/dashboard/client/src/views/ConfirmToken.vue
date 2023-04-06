<template>
    <div class="div"></div>
</template>

<script>

import axios from 'axios'

export default {
  data () {
    return {
    }
  },
  async mounted () {
    try {
      await axios.get('/confirmToken?token=' + this.$route.query.token)
      this.$router.push({ path: 'login' })
    } catch (error) {
      console.log(error)
    }
  }
}
</script>

<style>

</style>
