<template>
  <div class="home">
    <CardTemplate
      v-for="(elem) in allAREA"
      :key="elem.id"
      :id="elem.id"
      :title="elem.serviceActionName + ': ' + elem.actionName + ' to ' + elem.serviceReactionName + ': ' + elem.reactionName"
      :description="elem.description"
      :state="elem.state"
    >
    </CardTemplate>
    <div class="is-size-1 " v-if="allAREA.length == 0"> Create a new AREA first ! </div>
  </div>
</template>

<script>
// @ is an alias to /src
import CardTemplate from '@/components/ComponentTemplate';
import axios from 'axios';
export default {
  name: 'Home',
  components: {
    CardTemplate
  },
  data() {
    return {
      allAREA: []
    }
  },
  methods: {
    async getAreas() {
      try {
        const token = localStorage.getItem("area-token");
        const header = {
          "Content-Type": 'application/json; charset=UTF-8',
          "authorization": `Bearer ${token}`
        }
        const res = await axios.get("http://localhost:8080/api/component", {headers: header});
        this.allAREA = res.data.data
      } catch (error) {
        if (error.response && error.response.status && error.response.status === 403) {
          localStorage.setItem('area-token', null);
          this.$router.push('/');
        }
        console.log(error.message);
      }
    },
    async checkState() {
      setInterval(() => {
        this.getAreas();
      }, 3000)
    }
  },
  mounted() {
    this.getAreas();
    this.checkState();
  }
}
</script>
