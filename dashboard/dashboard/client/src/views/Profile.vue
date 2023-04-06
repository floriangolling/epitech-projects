<template>
   <section class="hero is-default is-bold is-fullheight-with-navbar">
        <div class="hero-body">
            <div class="container has-text-centered">
                <div class="column is-4 is-offset-4 profileBox ">
                    <h3 class="title has-text-white"> {{ $t('Profile.profile') }} </h3>
                    <hr class="login-hr">
                    <p class="subtitle has-text-white"> {{ $t('Profile.welcome') }} {{ user.username }} !</p>
                    <div class="box has-text-centered has-text-black">
                        <div class="has-text-black"> {{ $t('Profile.username') }}: {{user.username }} </div>
                        <div class="has-text-black mt-3"> Email: {{user.email }} </div>
                        <div class="has-text-black mt-3"> {{ $t('Profile.number') }}: {{ user.numberOfWidgets }} </div>
                        <div class="has-text-black mt-6"> Authentifications: </div>
                        <div class="mt-5 mb-2" v-for="auth in oauths" v-bind:key="auth">
                          <button class="button is-danger mr-4" :disabled="!user.oauths[auth] || !user.oauths[auth].refresh_token" @click="disconnectOauth(auth)"> Disconnect </button>
                          <button class="button is-info" :disabled="user.oauths[auth] && user.oauths[auth].refresh_token" @click="Auth(auth)"> {{auth}} </button>
                          <div class="ml-3 mb-2" v-if="isConnected"> {{ $t('Profile.alreadyConnected') }} </div>
                        </div>
                        <div class="mt-2"> {{ $t('Profile.changePassword') }} </div>
                        <input class="input mt-2" style="width:70%" type="password" placeholder="" v-model="password">
                        <div class="buttons is-centered">
                          <button class="button mt-2 is-info is-light has-text-centered is-centered" @click="changePassword"> {{ $t('Profile.apply') }} </button>
                        </div>
                        <div class="mt-2"> {{ $t('Profile.changeUsername') }} </div>
                        <input class="input mt-2" type="text" placeholder="" style="width:70%" v-model="username">
                        <div class="buttons is-centered">
                          <button class="button mt-2 is-info is-light has-text-centered is-centered" @click="changeUsername"> {{ $t('Profile.apply') }} </button>
                        </div>
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
      user: {
        name: '',
        email: '',
        numberOfWidgets: null,
        oauths: {}
      },
      oauths: [],
      username: '',
      password: ''
    }
  },
  async mounted () {
    try {
      const oauthsRequest = await axios.get('/oauths')
      this.oauths = oauthsRequest.data
      const request = await axios.get('/api/user', {
        headers: {
          authorization: localStorage.getItem('dashboard-token')
        }
      })
      this.user = request.data
    } catch (error) {
      if (error.response && (error.response.status === 404 || error.response.status === 403 || error.response.status > 400)) {
        this.$root.$emit('tokenChanged', null)
        localStorage.removeItem('dashboard-token')
        this.$router.push({ path: 'login' })
      }
      console.log(error)
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
    async disconnectOauth (name) {
      try {
        if (!this.user.canDisconnectOauth) {
          this.$toast.open({
            type: 'error',
            message: 'Please set a password to your account before trying to login'
          })
        } else {
          await axios.put('/api/user/' + this.user.id, {
            auth: name
          }, { headers: { authorization: localStorage.getItem('dashboard-token') } })
          this.$toast.open({
            type: 'success',
            message: `${name} successfully disconnected`
          })
          const request = await axios.get('/api/user', {
            headers: {
              authorization: localStorage.getItem('dashboard-token')
            }
          })
          this.user = request.data
        }
      } catch (error) {
        console.log(error)
        this.$toast.open({
          type: 'error',
          message: error
        })
      }
    },
    async changeUsername () {
      try {
        if (this.username.length < 4) {
          this.$toast.open({
            type: 'error',
            message: 'username too short'
          })
          return
        }
        await axios.put('/api/user/' + this.user.id, {
          username: this.username
        }, { headers: { authorization: localStorage.getItem('dashboard-token') } })
        this.$toast.open({
          type: 'success',
          message: 'username successfully changed'
        })
        const request = await axios.get('/api/user', {
          headers: {
            authorization: localStorage.getItem('dashboard-token')
          }
        })
        this.user = request.data
        this.username = ''
      } catch (error) {
        this.$toast.open({
          type: 'error',
          message: error
        })
        console.log(error)
      }
    },
    async changePassword () {
      try {
        if (this.password.length < 4) {
          this.$toast.open({
            type: 'error',
            message: 'password too short'
          })
          return
        }
        await axios.put('/api/user/' + this.user.id, {
          password: this.password
        }, { headers: { authorization: localStorage.getItem('dashboard-token') } })
        this.$toast.open({
          type: 'success',
          message: 'password successfully changed'
        })
        const request = await axios.get('/api/user', {
          headers: {
            authorization: localStorage.getItem('dashboard-token')
          }
        })
        this.user = request.data
        this.password = ''
      } catch (error) {
        this.$toast.open({
          type: 'error',
          message: error
        })
        console.log(error)
      }
    }
  }
}
</script>

<style>

.profileBox {
  background-color: #045de9 !important;
  background-image: linear-gradient(315deg, #045de9 0%, #52c1ec 74%) !important;
  border-radius: 25px !important;
}

</style>
