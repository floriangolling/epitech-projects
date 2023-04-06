<template>
  <section class="hero is-light is-fullheight-with-navbar">
    <div class="hero-body">
<div class="container has-text-centered">
                <div class="column is-4 is-offset-4 profileBox">
                    <h3 class="title has-text-white"> {{ $t('forgot.title') }} </h3>
                    <hr class="login-hr">
                    <p class="subtitle has-text-white"> {{ $t('forgot.email') }} </p>
                    <div class="box">
                            <div class="field mt-5">
                                <div class="control">
                                    <input class="input is-large" type="email" placeholder="Your Email" v-model="email">
                                </div>
                            </div>
                            <button @click="changePassword" class="button is-block is-success is-large is-fullwidth"> Send mail <i class="fa fa-sign-in" aria-hidden="true"></i></button>
                    </div>
                </div>
            </div>
    </div>
  </section>
</template>

<script>

import axios from 'axios'

export default {
  data () {
    return {
      email: ''
    }
  },
  methods: {
    async changePassword () {
      try {
        await axios.post('/forgot', {
          email: this.email
        })
        this.$toast.open({
          type: 'success',
          message: `Forgot password email has been sent to ${this.email}`
        })
        this.email = ''
      } catch (error) {
        console.log(error)
        this.$toast.open({
          type: 'error',
          message: 'An error has occured'
        })
        this.email = ''
      }
    }
  }
}
</script>

<style lang="scss">

</style>
