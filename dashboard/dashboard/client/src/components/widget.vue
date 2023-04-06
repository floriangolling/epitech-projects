<template>
    <div v-if="widgetInfo[0]" style="height:100%">
        <div class="columns">
            <div class="column">
                <div class="buttons has-text-centered is-centered">
                    <button class="button is-small" @click="hideWidget" style="border-radius:8px;color:black">
                        <span class="icon is-small">
                         <i class="fas fa-cog"></i>
                        </span>
                        </button>
                      <button class="button is-small is-success" style="border-radius:8px;background-color:#9191e8;color:white" @click="refreshWidget">
                        <span class="icon is-small">
                         <i class="fa fa-refresh"></i>
                        </span>
                      </button>
                </div>
            </div>
            <div class="column">
                <div class="my-title">
                    {{widget.serviceName}}
                </div>
                <div class="my-subtitle">
                    {{widget.widgetName}}
                </div>
            </div>
            <div class="column">
                <div class="buttons has-text-centered is-centered ml-3">
                    <button class="button is-danger is-small" @click="deleteWidget" style="border-radius:8px">
                        <span class="icon is-small">
                         <i class="fas fa-times"></i>
                        </span>
                        </button>
                </div>
            </div>
        </div>
        <transition name="fade">
          <div v-show="hidden">
            <div class=" my-subtitle"> {{widgetInfo[0].properties.params.name }}: </div>
            <input class="input has-text-centered mt-3" style="width:80%" v-model="widget.param" v-on:keyup.enter="changeParameter">
            <div class=" my-subtitle mt-3"> Refresh time (sc): </div>
            <input class="input has-text-centered mt-3" style="width:80%" v-model="widget.refreshTime" v-on:keyup.enter="changeRefreshTime">
            <div class="buttons has-text-centered is-centered mt-3">
              <button class="button is-success is-centered has-text-centered is-small" @click="saveBoth">
                Apply changes
              </button>
            </div>
          </div>
        </transition>
        <div v-html="widget.data"> </div>
    </div>
</template>

<script>

import axios from 'axios'

export default {
  data () {
    return {
      widgetInfo: {},
      interval: null,
      hidden: false
    }
  },
  props: {
    widget: Object
  },
  mounted () {
    try {
      const widgets = this.$store.getters.getWidgets
      this.widgetInfo = widgets.filter(wid => wid.properties.name === this.widget.widgetName)
      this.interval = window.setInterval(() => {
        this.refreshWidget()
      }, this.widget.refreshTime * 1000)
    } catch (error) {
      console.log(error)
    }
  },
  methods: {
    async deleteWidget () {
      this.$root.$emit('deleteWidget', this.widget.i)
    },
    async refreshWidget () {
      try {
        const request = await axios.get('/api/widget/' + this.widget.i, {
          headers: {
            authorization: localStorage.getItem('dashboard-token')
          }
        })
        this.widget.data = request.data
      } catch (error) {
        console.log(error)
      }
    },
    async changeParameter () {
      try {
        await axios.put('/api/widget/' + this.widget.i, {
          parameter: this.widget.param
        }, {
          headers: {
            authorization: localStorage.getItem('dashboard-token')
          }
        })
        this.$toast.open({
          type: 'success',
          message: 'Parameter saved !'
        })
        this.refreshWidget()
      } catch (error) {
        console.log(error)
      }
    },
    async changeRefreshTime () {
      try {
        if (this.widget.refreshTime <= 0) {
          this.$toast.open({
            type: 'error',
            message: 'Time must be bigger than 0 !'
          })
        }
        await axios.put('/api/widget/' + this.widget.i, {
          refreshTime: this.widget.refreshTime
        }, {
          headers: {
            authorization: localStorage.getItem('dashboard-token')
          }
        })
        clearInterval(this.interval)
        this.interval = window.setInterval(() => {
          this.refreshWidget()
        }, this.widget.refreshTime * 1000)
        this.$toast.open({
          type: 'success',
          message: 'RefreshTime saved !'
        })
      } catch (error) {
        console.log(error)
      }
    },
    async hideWidget () {
      this.hidden = !this.hidden
    },
    async saveBoth () {
      try {
        await this.changeParameter()
        await this.changeRefreshTime()
      } catch (error) {
        console.log(error)
      }
    }
  }
}
</script>

<style>

.fade-enter-active, .fade-leave-active {
  transition: opacity .5s;
}

.my-title {
    font-size: 1.5rem;
    font-weight: 900;
}

.my-subtitle {
    font-size: 1rem;
    font-weight: 400;
}

</style>
