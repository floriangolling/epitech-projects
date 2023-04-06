<template>
  <div class="container">
    <img src="../assets/logoarea.png" />
    <h1 class="is-size-3 has-text-weight-bold">Login</h1>
    <br />
    <input
        type="text"
        name="email"
        id="email"
        placeholder="Email adress"
        v-model="login.email"
    />
    <br />
    <br />
    <input
        type="password"
        name="password"
        id="password"
        placeholder="Password"
        v-model="login.password"
    />
    <br/>
    <button class="button is-black mt-6 is-large" @click="sendLogin()"> Login </button>
    <div class="mb-2 mt-5">
      Login with :
    </div>
    <button class="button is-white" v-for="oauth in oauths" :key="oauth.name" @click="sendOauth(oauth)">
      {{oauth}}
    </button>
    <br />
    <p class="mt-2">
      <router-link to="/register">Sign up</router-link>
    </p>
  </div>
</template>

<script>
import axios from 'axios';
import 'vue-toast-notification/dist/theme-sugar.css';

export default {
  name: "Login",
  //Custom style for main and input for make the page responsive:
  data () {
    return {
      login: {
        email: "",
        password: ""
      },
      oauths: []
    };
  },
  methods: {
    async sendLogin() {
       try {
          const res = await axios.post("http://localhost:8080/login", {
            password: this.login.password,
            username: this.login.email,
          })
          localStorage.setItem('area-token', res.data.token);
          this.$router.push('/myarea');
       } catch (error) {
         this.$toast.open({message: "Email or Password invalid", type: "error"});
       }
    },
    async getAvailableOAuth() {
      if (localStorage.getItem("area-token") != null && localStorage.getItem("area-token") != "null")
        this.$router.push('/myarea');
      try {
        const res = await axios.get("http://localhost:8080/oauths/create");
        this.oauths = res.data.oauths;
        console.log(this.oauths);
      } catch (error) {
        console.log(error);
      }
    },
    async sendOauth(serviceName) {
      try {
        console.log(serviceName);
        const res = await axios.get(`http://localhost:8080/auth/link/${serviceName}`);
        location.assign(res.data.message);
      } catch (error) {
        console.log(error);
      }
    }
  },
  mounted() {
    this.getAvailableOAuth();
  }
}
</script>

<style>
</style>
