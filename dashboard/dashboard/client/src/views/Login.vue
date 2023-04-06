<template>
  <section class="hero is-light is-fullheight-with-navbar">
    <div class="hero-body">
<div class="container has-text-centered">
                <div class="column is-4 is-offset-4 profileBox">
                    <h3 class="title has-text-white">{{ $t('Login.title') }}</h3>
                    <hr class="login-hr">
                    <p class="subtitle has-text-white">{{ $t('Login.subtitle') }}</p>
                    <div class="box">
                            <div class="field">
                                <div class="control">
                                    <input class="input is-large" type="email" placeholder="Your Email" v-model="email">
                                </div>
                            </div>
                            <div class="field">
                                <div class="control">
                                    <input class="input is-large" type="password" placeholder="Your Password" v-model="password">
                                </div>
                            </div>
                            <button @click="logInAccount" class="button is-block is-success is-large is-fullwidth">{{ $t('Login.button') }}<i class="fa fa-sign-in" aria-hidden="true"></i></button>
                            <div class="mt-4 mb-2"> {{ $t('Login.oauths') }} </div>
                            <div v-for="auth in oauths" v-bind:key="auth">
                              <div class="buttons mt-5 is-centered">
                                <button class="button is-info is-centered has-text-centered" v-bind:class="{twitchButton: auth.includes('twitch') }" @click="Auth(auth)"> {{auth}}
                                   <i  v-if="auth == 'twitch'" class="fab fa-twitch ml-3"></i>
                                </button>
                              </div>
                            </div>
                    </div>
                    <p class="has-text-white">
                        <a href="/register">{{ $t('Login.signup') }}</a> &nbsp;·&nbsp;
                        <a href="/forgotPassword">{{ $t('Login.password') }}</a> &nbsp;·&nbsp;
                        <a href="/">{{ $t('Login.help') }}</a>
                    </p>
                </div>
            </div>
    </div>
  </section>
</template>

<script>
const axios = require('axios')
export default {
  async mounted () {
    try {
      const oauthsRequest = await axios.get('/oauths')
      this.oauths = oauthsRequest.data
    } catch (error) {
      console.log(error)
    }
  },
  data () {
    return {
      email: '',
      password: '',
      oauths: []
    }
  },
  methods: {
    async logInAccount () {
      try {
        const request = await axios.post('/login',
          { email: this.email, password: this.password })
        if (request.status === 200) {
          localStorage.setItem('dashboard-token', request.data)
          this.$root.$emit('tokenChanged', request.data)
          this.$router.push({ path: 'dashboard' })
        }
      } catch (err) {
        if (err.response && err.response.status === 403) {
          this.$toast.error('Please confirm your email.')
        } else {
          this.$toast.error('An error occured while trying to login')
        }
        console.log(err)
      }
    },
    async Auth (name) {
      try {
        const request = await axios.get('/auth/link/' + name)
        window.location.replace(request.data)
      } catch (error) {
        console.log(error)
      }
    }
  }
}
</script>

<style lang="scss">

.twitchButton {
  background-color: #ce10ce !important;
}

</style>
