<template>
  <div id="app">
    <navbar></navbar>
    <div>
      <router-view/>
    </div>
  </div>
</template>

<script>

import Navbar from './components/Navbar.vue'

export default {
  components: {
    Navbar
  },
  async mounted () {
    if (localStorage.getItem('lang')) {
      this.$root.$i18n.locale = localStorage.getItem('lang')
    }
    this.$root.$on('lang', async (lang) => {
      this.$root.$i18n.locale = lang
      localStorage.setItem('lang', lang)
    })
  }
}

</script>

<style lang="scss">

</style>
