<template>
    <div class="div">
        {{ $t('Callback.redi') }}
    </div>
</template>

<script>

import axios from 'axios'

export default {
  async mounted () {
    try {
      const request = await axios.get(`/auth/callback/${this.$route.params.id}?code=${this.$route.query.code}&scope=${this.$route.query.scope}`, {
        headers: {
          authorization: localStorage.getItem('dashboard-token')
        }
      })
      if (request.status === 200) {
        localStorage.setItem('dashboard-token', request.data)
        this.$root.$emit('tokenChanged', request.data)
        this.$router.push({ path: '/dashboard' })
      } else {
        this.$router.push({ path: '/profile' })
      }
    } catch (error) {
      console.log(error)
    }
  }
}
</script>

<style>

</style>
