<template>
    <div class="card mt-6 container has-background-dark" style="border-radius: 50px">
        <div class="card-content">
            <div class="media">
            <div class="media-content">
                <p class="title is-4 has-text-white">{{title}}</p>
                <p class="subtitle is-6 has-text-white">{{description}}</p>
            </div>
            </div>
            <div class="content has-text-white" v-if="!state">
                State: Off
            </div>
            <div class="content has-text-white" v-if="state">
                State: On
            </div>
        </div>
        <footer class="card-footer">
            <a class="card-footer-item has-text-white" @click="deleteComponent()">Delete</a>
        </footer>
    </div>
</template>

<script>
import axios from 'axios';
export default {
    props: {
        id: Number,
        title: String,
        description: String,
        state: Boolean,
    },
    methods: {
      async deleteComponent() {
        try {
          const token = localStorage.getItem("area-token");
          const header = {
            "Content-Type": 'application/json; charset=UTF-8',
            "Authorization": `Bearer ${token}`
          }
          await axios.delete(`http://localhost:8080/api/component/${this.id}`, {headers: header});
          this.$router.go();
        } catch (error) {
          console.log(error.message);
        }
      }
    }
}
</script>

<style>
.myWidget {
  max-width: 100%;
  margin: 20px 30px;
  width: 250px;
  border: solid 2px black;
  border-radius: 10px;
}

.myWidget-content {
  padding: 12px;
  background-color: #d4d4d4;
  border-radius: 0 0 8px 8px;
}

.myWidget-content h2 {
  display: flex;
  justify-content: left;
  font-size: 24pt;
}

.myWidget-content p {
  margin-bottom: 5px;
}

.listWidgets {
  display: flex;
  flex-direction: column;
}

.listWidgets button {
  width: 70%;
  margin: 0 auto 12px auto;
}

.myFieldSet {
  display: flex;
  flex-direction: column;
  padding: 0 5px;
  margin: 10px 0;
}

.myFieldSet input {
  padding: 0;
}

.myFieldSet label {
  font-weight: 500;
}

.buttonControl {
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  border-radius: 7px 7px 0 0;
  background-color: white;
  /* padding: 10px 0; */
}

.buttonControl button {
  background: rgba(0,0,0,0);
  max-height: 40px;
  max-width: 40px;
  padding: 6px;
}

.buttonControl button img {
  max-width: 100%;
  max-height: 100%;
}
</style>