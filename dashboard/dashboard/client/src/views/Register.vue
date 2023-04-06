<template>
  <section class="hero is-light is-fullheight-with-navbar">
    <div class="hero-body">
<div class="container has-text-centered">
                <div class="column is-4 is-offset-4 profileBox">
                    <h3 class="title has-text-white">{{ $t('Register.title') }}</h3>
                    <hr class="login-hr">
                    <p class="subtitle has-text-white">{{ $t('Register.subtitle') }}</p>
                    <div class="box">
                            <div class="field">
                                <div class="control">
                                    <input class="input is-large" type="email" placeholder="Email" v-model="email">
                                </div>
                            </div>
                            <div class="field">
                                <div class="control">
                                    <input class="input is-large" type="password" placeholder="Password" v-model="password">
                                </div>
                            </div>
                            <div class="field">
                                <div class="control">
                                    <input class="input is-large" type="password" placeholder="Repeat your password" v-model="repeatPassword">
                                </div>
                            </div>
                            <div class="field">
                                <div class="control">
                                    <input class="input is-large" type="text" placeholder="Nickname" v-model="username">
                                </div>
                            </div>
                            <button @click="createAccount" class="button is-block is-success is-large is-fullwidth">{{ $t('Register.button') }} <i class="fa fa-sign-in" aria-hidden="true"></i></button>
                            <div class="mt-4 mb-2"> {{ $t('Register.oauths') }} </div>
                            <div v-for="auth in oauths" v-bind:key="auth">
                              <div class="buttons mt-5 is-centered">
                                <button class="button is-info is-centered has-text-centered" v-bind:class="{twitchButton: auth.includes('twitch') }" @click="Auth(auth)"> {{auth}}
                                   <i class="fab fa-twitch ml-3"></i>
                                   </button>
                              </div>
                            </div>
                    </div>
                    <p class="has-text-white">
                        <a href="/login">{{ $t('Register.signup') }}</a> &nbsp;·&nbsp;
                        <a href="/forgotPassword">{{ $t('Register.password') }}</a> &nbsp;·&nbsp;
                        <a href="/">{{ $t('Register.help') }}</a>
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
      repeatPassword: '',
      username: '',
      oauths: []
    }
  },
  methods: {
    async Auth (name) {
      try {
        const request = await axios.get('/auth/link/' + name)
        window.location.replace(request.data)
      } catch (error) {
        console.log(error)
      }
    },
    async createAccount () {
      try {
        if (this.email.size <= 1) {
          return
        }
        if (this.username.size <= 4) {
          return
        }
        if (this.password !== this.repeatPassword || this.password <= 4) {
          return
        }
        const request = await axios.post('/register',
          { email: this.email, password: this.password, username: this.username })
        if (request.status === 201) {
          this.email = ''
          this.password = ''
          this.repeatPassword = ''
          this.username = ''
          this.$toast.open({
            type: 'success',
            message: 'Please confirm your account before trying to login'
          })
        }
      } catch (err) {
        if (err.response && err.response.status === 409) {
          this.$toast.open({
            type: 'error',
            message: 'Adress already used'
          })
        }
        console.log(err)
      }
    }
  }
}
</script>
