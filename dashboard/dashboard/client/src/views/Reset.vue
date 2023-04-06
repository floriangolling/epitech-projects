<template>
    <section class="hero is-light is-fullheight-with-navbar">
    <div class="hero-body">
        <div class="container has-text-centered">
                <div class="column is-4 is-offset-4 profileBox">
                    <h3 class="title has-text-white"> {{ $t('reset.title') }} </h3>
                    <hr class="login-hr">
                    <p class="subtitle has-text-white"> {{ $t('reset.email') }} </p>
                    <div class="box">
                            <div class="field mt-5">
                                <div class="control">
                                    <input class="input is-large" type="password" placeholder="Your new password" v-model="password">
                                </div>
                            </div>
                            <button @click="changePassword" class="button is-block is-success is-large is-fullwidth"> Change password <i class="fa fa-sign-in" aria-hidden="true"></i></button>
                    </div>
                </div>
            </div>
    </div>
  </section>
</template>

<script>

import axios from 'axios'

export default {
  methods: {
    async changePassword () {
      if (this.password.length < 4) {
        this.$toast.open({
          type: 'error',
          message: 'Password not long enough'
        })
        return
      }
      try {
        await axios.post('/resetPassword', {
          password: this.password,
          token: this.$route.query.token
        })
        this.$toast.open({
          type: 'success',
          message: 'password changed !'
        })
        this.password = ''
        setTimeout(function () {
          this.$router.push({ path: 'login' })
        }, 1000)
      } catch (error) {
        this.$toast.open({
          type: 'error',
          message: error
        })
      }
    }
  },
  data () {
    return {
      password: ''
    }
  }
}
</script>

<style lang="scss">

</style>
