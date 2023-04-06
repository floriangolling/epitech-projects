<template>
  <div id="app">
    <nav class="navbar has-background-dark" role="navigation" aria-label="main navigation">
        <div class="navbar-brand">
          <a class="navbar-item">
            <h1 class="title has-text-white">AREA</h1>
          </a>

          <button @click="openBurger()" class="button navbar-burger is-dark" data-target="navMenu" v-if="isJWT()" v-bind:class="{ 'is-active': activated }">
              <span></span>
              <span></span>
              <span></span>
          </button>
        </div>
        <div id="navMenu" class="navbar-menu has-background-dark" v-bind:class="{ 'is-active': activated }">
          <div class="navbar-start">
            <a class="navbar-item txt-white" v-if="isJWT()" href="/myarea">
              My AREAs
            </a>

            <a class="navbar-item txt-white" v-if="isJWT()" href="/create">
              New AREA
            </a>
            <a class="navbar-item txt-white" v-if="isJWT()" href="/profile">
              Profile
            </a>
          </div>
          <div class="navbar-end" v-if="isJWT()">
            <div class="navbar-item">
              <div class="buttons">
                <button class="button is-light" @click="resetJwt()">
                  Logout
                </button>
              </div>
            </div>
          </div>
      </div>
    </nav>
    <router-view/>
  </div>
</template>

<script>
export default {
  name: 'App',

  data: () => ({
    //
    activated: false,
  }),
  methods: {
    isJWT() {
      if (localStorage.getItem("area-token") != "null" && localStorage.getItem("area-token") != null) {
        return true;
      } else {
        return false;
      }
    },
    resetJwt() {
      localStorage.setItem("area-token", null);
      this.$router.push('/');
    },
    openBurger() {
      this.activated = !this.activated;
      return this.activated;
    }
  }
};
</script>

<style lang="scss">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

.title {
  font-weight: bold;
}

.txt-white {
  color: white !important;
}

.txt-white:hover {
  color:black !important;
}

.txt-black {
  color: black !important;
}

#nav {
  padding: 30px;

  a {
    font-weight: bold;
    color: #2c3e50;
    &.router-link-exact-active {
      color: #42b983;
    }
  }
}

.nav {
  a:hover {
    color: black ;
  }
}
</style>
