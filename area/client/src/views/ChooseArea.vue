<template>
  <div>
    <h1 class="has-text-centered has-text-weight-bold"> Create a new AREA </h1>
    <div class="zebi">
      <button class="button lol mb-5" style="background-color: #0a0a0a" @click="showModalAction"> {{action}} </button>
      <button class="button lol" style="background-color: #9e9e9e" @click="showModalReaction"> {{reaction}} </button>
    </div>
      <section class="section">
      <div class="modal" :class="{'is-active': showModalFlag}">
        <div class="modal-background"></div>
        <div class="modal-card">
          <header class="modal-card-head">
            <p class="modal-card-title">{{titleModal}}</p>
            <button class="delete" aria-label="close" @click="cancelModal">></button>
          </header>
          <section class="modal-card-body">
            <div class="listServices" v-if="showServices == true && !showActions">
                <button
                  class="button is-dark"
                  v-for="value in availableServices"
                  :key="value.name"
                  @click="getAvailableAREA(value.name)"
                >
                  {{ value.name }} service
                </button>
            </div>
            <div class="listWidgets" v-if="showActions == true && !showServices">
              <div v-for="value in availableActions"
                  :key="value.name">
                <button class="button is-dark" @click="changeTitle('action', value.description, value.name)">
                  {{ value.description }}
                </button>
              </div>
            </div>
            <div class="listWidgets" v-if="showReaction == true && !showServices">
              <div v-for="value in availableReactions"
                :key="value.name">
                <button class="button is-dark is-fullwidth is-responsive" @click="changeTitle('reaction', value.description, value.name)">
                  {{ value.description }}
                </button>
              </div>
            </div>
        </section>
        <footer class="modal-card-foot">
          <button class="button" @click="cancelModal">Cancel</button>
        </footer>
      </div>
    </div>
  </section>
    <button class="button is-black is-large" @click="submitAREA">
            Confirm
    </button>
  </div>
</template>

<script>
import axios from "axios";
export default {
  name: "create",
  data() {
    return {
      showModalFlag: false,
      availableServices: {},
      showServices: false,
      availableActions: {},
      availableReactions: {},
      choice: "",
      showActions: false,
      showReaction: false,
      action: "If This",
      reaction: "Then that",
      nameService: "",
      titleModal: "Choose a Service",
      reactionName: "",
      actionName: "",
      serviceActionName: "",
      serviceReactionName: "",
    }
  },
  methods: {
    async getAvailable() {
      const res = await axios.get("http://localhost:8080/api/service");
      this.availableServices = res.data.services;
    },
    getAvailableAREA(name) {
      for (let i = 0; i < this.availableServices.length; ++i) {
        if (this.availableServices[i].name == name) {
          this.availableActions = this.availableServices[i].actions;
          this.availableReactions = this.availableServices[i].reactions;
          this.nameService = name;
        }
      }
      if (this.choice == "action") {
        this.showActions = true;
        this.titleModal = "Choose an Action";
      }
      else if (this.choice == "reaction") {
        this.showReaction = true;
        this.titleModal = "Choose a Reaction";
      }
      this.showServices = false;
    },
    changeTitle(type, newTitle, name) {
      if (type == "action") {
        this.action = "If " + newTitle;
        this.actionName = name;
        this.serviceActionName = this.nameService;
      }
      else if (type == "reaction") {
        this.reaction = "Then " + newTitle;
        this.reactionName = name;
        this.serviceReactionName = this.nameService;      
      }
      this.showModalFlag = false;
      this.showActions = false;
      this.showServices = false;
      this.showReaction = false;
      this.availableActions = {};
      this.availableReactions = {};
      this.titleModal = "Choose a Service";
    },
    async submitAREA() {
      try {
        const token = localStorage.getItem("area-token");
        const header = {
          "Content-Type": 'application/json; charset=UTF-8',
          "Authorization": `Bearer ${token}`
        }
        await axios.post("http://localhost:8080/api/component", {reactionName: this.reactionName, serviceActionName: this.serviceActionName, actionName: this.actionName, serviceReactionName: this.serviceReactionName}, {headers: header});
        this.action = "If This";
        this.reaction = "Then that";
        this.$toast.open({message: "AREA created successfully !", type: "success"});
      } catch (error) {
        if (error.response && error.response.status && error.response.status === 403) {
          localStorage.setItem('area-token', null);
          this.$router.push('/');
        }
        console.log(error.message);
      }
    },
    showModalAction() {
      this.showModalFlag = true;
      this.showServices = true;
      this.choice = "action";
    },
      showModalReaction() {
      this.showModalFlag = true;
      this.showServices = true;
      this.choice = "reaction";
    },
    async cancelModal() {
      this.showModalFlag = false;
      this.showActions = false;
      this.showServices = false;
      this.showReaction = false;
      this.availableActions = {};
      this.availableReactions = {};
      this.titleModal = "Choose a Service";
    }
  },
  mounted() {
    this.getAvailable();
  }
}
</script>

<style scoped>

h1 {
  font-size: 50px;
  margin-top: 3%;
}

.listServices {
  display: flex;
  flex-direction: column;
}

.listServices button {
  width: 40%;
  margin: 0 auto 12px auto;
}

.listWidgets {
  display: flex;
  flex-direction: column;
}

.listWidgets button {
  margin: 0 auto 12px auto;
}

.zebi {
  display: flex;
  flex-direction: column;
  width: 70%;
  margin-left: 15%;
  margin-top: 5%;
}

.lol {
  font-size: 30px;
  word-break: break-word;
  height: fit-content;
  color: white;
  border-radius: 3rem;
}

.button {
  white-space: normal;
}

</style>