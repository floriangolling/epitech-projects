<template>
    <pre> {{ json }} </pre>
</template>

<script>

import axios from 'axios'

export default {
  data () {
    return {
      json: {}
    }
  },
  async mounted () {
    try {
      const request = await axios.get('/about.json')
      this.json = request.data
    } catch (error) {
      this.json = { error: 'error' }
      console.log(error)
    }
  }
}
</script>

<style>

</style>
