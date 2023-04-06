<template>
  <div class="container">
    <img src="../assets/logoarea.png" />
    <h1>Enter your email</h1>
    <br />
    <input
        type="text"
        name="email"
        id="email"
        placeholder="Email adress"
        v-model="register.email"
    />
    <br />
    <br />
    <h1>Enter your password</h1>
    <br />
    <input
        type="password"
        name="password"
        id="password"
        placeholder="Password"
        v-model="register.password"
    />
    <br />
    <br />
    <h1>Repeat your password</h1>
    <br />
    <input
        type="password"
        name="password"
        id="repeatpassword"
        placeholder="Repeat password"
        v-model="register.repeatPassword"
    />
    <br/>
    <br/>
    <button class="button is-black mt-3 mb-5 is-medium" @click="sendRegister()"> Sign up </button>
    <p>
      <router-link to="/">Login</router-link>
    </p>
  </div>
</template>

<script>
import axios from 'axios';
import 'vue-toast-notification/dist/theme-sugar.css';
export default {
  name: "Login",
  //Custom style for main and input for make the page responsive:
  props: {
    mainStyle: String,
    inputStyle: String,
  },
  data() {
    return {
      register: {
        email: "",
        password: "",
        repeatPassword: "",
      }
    };
  },
  methods: {
    check (password, repeatPassword) {
      if (password != repeatPassword || this.register.email == "" || password == "")
        return false;
      return true;
    },
    async sendRegister() {
      try {
          if (!this.check(this.register.password, this.register.repeatPassword)) {
            this.$toast.open({message: "Passwords have to be the same", type: "error"});
            return;
          }
          const res = await axios.post("http://localhost:8080/register", {
            password: this.register.password,
            username: this.register.email,
          })
          this.$toast.open({message: res.data.message, type: "success"});
          this.$router.push("/");
       } catch (error) {
         console.log(error.message);
       }
    } 
  }
};
</script>

<style>
/* Import Poppins font: */
@import url("https://fonts.googleapis.com/css2?family=Poppins&display=swap");
.main {
  background: rgba(255, 255, 255, 0.4);
  position: absolute;
  top: 5%;
  left: 30%;
  width: 40%;
  text-align: center;
  border-radius: 3rem;
  box-shadow: 0px 0px 8px -5px #000000;
  padding-top: 3%;
  padding-bottom: 5%;
  font-family: "Poppins", sans-serif;
}
h1 {
  cursor: default;
  user-select: none;
}
input {
  border-radius: 3rem;
  padding: 20px;
  text-align: center;
  outline: black;
  width: 30%;
  font-family: "Poppins", sans-serif;
  font-weight: 400;
}
input:hover {
  box-shadow: 0px 0px 8px -5px #000000;
}
input:active {
  box-shadow: 0px 0px 8px -5px #000000;
}
#done {
  background: lightgreen;
}
.button {
  cursor: pointer;
  user-select: none;
}
img {
  height: 2.2rem;
  margin: 10px;
  user-select: none;
}
img:hover {
  box-shadow: 0px 0px 8px -5px #000000;
  cursor: pointer;
  border-radius: 200rem;
}
</style>
