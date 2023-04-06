<template>
    <div>
        <div class="mt-5 is-size-2 has-text-weight-bold">
            Welcome, {{username}}
        </div>
        <div class="mt-6 is-size-3 mb-3"> Connect with : </div>
        <div class="columns is-half is-centered">
            <button class="button is-dark ml-5 mt-5" v-for="(elem) in disconnected" :key="elem" @click="sendOauth(elem)"> {{elem}}</button>
            <button class="button ml-5 mt-5 is-outline" v-for="(elem) in connected" :key="elem" @click="disconnectOauth(elem)"> {{elem}}</button>
        </div>
        <div class="mt-6 is-size-3 mb-3"> Change password : </div>
        <div class="is-size-4 mt-5 mb-3">Enter new password</div>
        <input
        class="mb-5"
        type="password"
        name="password"
        id="password"
        placeholder="Password"
        v-model="options.password"
        />
        <div class="is-size-4 mb-3">Repeat your password</div>
        <input
            type="password"
            name="password"
            id="repeatpassword"
            placeholder="Repeat password"
            v-model="options.repeatPassword"
        />
        <br/>
        <button class="button is-dark mt-6 is-large" @click="changePassword()"> Change Password</button>
    </div>
</template>
<script>
import axios from 'axios';
import 'vue-toast-notification/dist/theme-sugar.css';
export default {
    data() {
        return {
            allOauth: [],
            options: {
                passsword: "",
                repeatPassword: ""
            },
            username: "",
            connectedOauth: [],
            connected: [],
            disconnected: []
        };
    },
    methods: {
        async getOauth() {
            try {
                const token = localStorage.getItem("area-token");
                const header = {
                "Content-Type": 'application/json; charset=UTF-8',
                "Authorization": `Bearer ${token}`
                }
                const res = await axios.get("http://localhost:8080/oauths");
                this.allOauth = res.data.oauths;
                const resName = await axios.get("http://localhost:8080/me", {headers: header});
                this.username = resName.data.username;
                this.connectedOauth = resName.data.oauths;
                this.connected = [];
                this.disconnected = [];
                for (var i = 0; i < this.allOauth.length; ++i) {
                    if (this.isInclude(this.allOauth[i]))
                        this.connected.push(this.allOauth[i]);
                    else
                        this.disconnected.push(this.allOauth[i]);
                }
            } catch(error) {
                if (error.response && error.response.status && (error.response.status === 403 || error.response.status === 404)) {
                    localStorage.setItem('area-token', null);
                    this.$router.push('/');
                }
                console.log(error.message);
            }
        },
        async sendOauth (serviceName) {
            try {
                console.log(serviceName);
                const res = await axios.get(`http://localhost:8080/auth/link/${serviceName}`);
                location.assign(res.data.message);
            } catch (error) {
                console.log(error);
            }
        },
        async disconnectOauth(serviceName) {
            try {
                const token = localStorage.getItem("area-token");
                const header = {
                    "Content-Type": 'application/json; charset=UTF-8',
                    "Authorization": `Bearer ${token}`
                }
                const res = await axios.put(`http://localhost:8080/disconnect/${serviceName}`, {}, {headers: header});
                console.log(res.data);
                this.$toast.open({message: "You have been disconnected.", type: "success"});
                this.getOauth();
            } catch (error) {
                console.log(error.message);
            }
        },
        isInclude(name) {
            return this.connectedOauth.includes(name);
        },
        check(password, repeatPassword) {
            if (password != repeatPassword || password == "")
                return false;
            return true;
        },
        async changePassword() {
            if (!this.check(this.options.password, this.options.repeatPassword)) {
                this.$toast.open({message: "Passwords have to be the same", type: "error"});
                return;
            }
            try {
                const token = localStorage.getItem("area-token");
                const header = {
                "Content-Type": 'application/json; charset=UTF-8',
                "Authorization": `Bearer ${token}`
                }
                const res = await axios.put("http://localhost:8080/password", {password: this.options.password}, {headers: header});
                console.log(res.data);
                this.options.password = "";
                this.options.repeatPassword = "";
                this.$toast.open({message: "Password changed!", type: "success"});
            } catch (error) {
                this.$toast.open({message: "An error occured", type: "error"});
                console.log(error.message);
            }
        }
    },
    mounted() {
        this.getOauth();
    }
};
</script>
<style scoped>
</style>