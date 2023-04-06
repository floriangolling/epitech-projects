<template>
    <b-navbar class="is-info">
        <template #brand>
            <b-navbar-item tag="router-link" :to="{ path: '/' }">
                <img src="../assets/dashboard-64.png">
            </b-navbar-item>
        </template>
        <template #start>
            <b-navbar-item tag="router-link" :to="{ path: '/' }">
                <strong> {{ $t('navBar.home') }} </strong>
            </b-navbar-item>
            <b-navbar-item tag="router-link" :to="{ path: '/dashboard' }" v-if="token">
                <strong> Dashboard </strong>
            </b-navbar-item>
            <b-navbar-item tag="router-link" :to="{ path: '/about' }" v-if="token">
                <strong> About.json </strong>
            </b-navbar-item>
        </template>

        <template #end>
            <b-navbar-item tag="div">
                <div class="buttons" v-if="token">
                    <a class="button is-danger" @click="onClickLogout">
                        <strong> {{ $t('navBar.logout') }}</strong>
                    </a>
                    <a class="button is-light" @click="onClickProfile">
                        {{ $t('navBar.profile') }}
                    </a>
                </div>
                <div class="buttons" v-else>
                    <a class="button is-danger" @click="onClickRegister">
                        <strong>{{ $t('navBar.signup') }}</strong>
                    </a>
                    <a class="button is-light" @click="onClickLogin">
                        {{ $t('navBar.login') }}
                    </a>
                </div>
            </b-navbar-item>
            <b-navbar-item tag="div">
              <img src="../assets/fr.png" alt="" @click="changeLang('fr')">
            </b-navbar-item>
            <b-navbar-item tag="div">
              <img src="../assets/en.png" alt="" @click="changeLang('en')">
            </b-navbar-item>
        </template>
    </b-navbar>
</template>

<script>

export default {
  methods: {
    async onClickLogin () {
      this.$router.push('login')
    },
    async onClickRegister () {
      this.$router.push('register')
    },
    async onClickLogout () {
      localStorage.removeItem('dashboard-token')
      this.token = null
      this.$router.push({ path: 'login' })
    },
    async onClickProfile () {
      this.$router.push({ path: 'profile' })
    },
    async changeLang (newLang) {
      this.$root.$emit('lang', newLang)
    }
  },
  data () {
    return {
      token: localStorage.getItem('dashboard-token')
    }
  },
  async mounted () {
    this.$root.$on('tokenChanged', async (token) => {
      this.token = token
    })
  }
}

</script>

<style lang="scss">

.navbar {
  background-color: #045de9 !important;
  background-image: linear-gradient(315deg, #045de9 0%, #52c1ec 74%) !important;
}

</style>
