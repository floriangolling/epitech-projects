<template>
  <div> Waiting for redirection... </div>
</template>

<script>

import axios from 'axios';

export default {
    async mounted() {
        try {
            let request;
            if (!localStorage.getItem('area-token')) {
                request = await axios.get(`http://localhost:8080/auth/callback/${this.$route.params.id}?code=${this.$route.query.code}&scope=${this.$route.query.scope}&state=${this.$route.query.state}&oauth_token=${this.$route.query.oauth_token}&oauth_verifier=${this.$route.query.oauth_verifier}`);

            } else {
                request = await axios.get(`http://localhost:8080/auth/callback/${this.$route.params.id}?code=${this.$route.query.code}&scope=${this.$route.query.scope}&state=${this.$route.query.state}&oauth_token=${this.$route.query.oauth_token}&oauth_verifier=${this.$route.query.oauth_verifier}`, {headers: {
                    'Authorization': `Bearer ${localStorage.getItem('area-token')}`
                }});
            }
            if (request.data.token) {
                localStorage.setItem('area-token', request.data.token);
                this.$router.push("/create");
            } else {
                this.$router.push("/profile");
            }
        } catch (error) {
            localStorage.setItem('area-token', null);
            this.$router.push('/');
            console.log('an error has occured');
        }
    }
}
</script>

<style>

</style>