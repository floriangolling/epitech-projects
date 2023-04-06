<template>
    <section class="hero is-fullheight-with-navbar is-light has-text-black">
        <template>
          <modal name="widget" :adaptive=true>
            <widget-form></widget-form>
          </modal>
        </template>
        <div>
            <grid-layout :layout.sync="layout" :col-num="10"
                         :row-height="30"
                         :is-draggable="draggable"
                         :is-resizable="resizable"
                         :responsive="true"
                         :vertical-compact="true"
                         :use-css-transforms="true"
                         :prevent-collision="false"
                        style="flex: 1;display: flex">
                <grid-item v-for="item in widgetList" v-bind:key="item.i" :static="item.static" :x="item.x" :y="item.y" :w="item.w" :h="item.h" :i="item.i" @moved="movedEvent(item.i, item.x, item.y)" v-bind:class="{ twitchWidget: item.serviceName.includes('Twitch'), weatherWidget: item.serviceName.includes('Weather'), dashboardWidget: item.serviceName == '', leagueWidget: item.serviceName.includes('League'), timeWidget: item.serviceName.includes('Time'), cryptoWiget: item.serviceName.includes('Crypto')}">
                  <template v-if="item.i == -1">
                    <div class="has-text-centered mt-3">
                      <span class="title has-text-white">
                        Dashboard
                      </span>
                      <div class="has-text-white mt-2">
                        {{ $t('Dashboard.welcome') }} {{name}} !
                      </div>
                        <button class="button is-success is-medium mt-5" @click="createWidget">
                           {{ $t('Dashboard.widget') }}
                        </button>
                    </div>
                  </template>
                  <template v-else>
                    <div class="has-text-centered mt-3" style="height:100%">
                      <widget :widget="item"></widget>
                    </div>
                  </template>
                </grid-item>
            </grid-layout>
        </div>
    </section>
</template>

<script>

import { GridLayout, GridItem } from 'vue-grid-layout'
import WidgetForm from '../components/WidgetForm.vue'
import Widget from '../components/widget.vue'
import axios from 'axios'

export default {
  components: {
    Widget,
    GridLayout,
    GridItem,
    WidgetForm
  },
  data () {
    return {
      name: '',
      i: 1,
      layout: [
        { x: 4, y: 0, w: 4, h: 5, i: -1, static: true, serviceName: '' }
      ],
      draggable: true,
      resizable: false,
      responsive: true,
      index: 0,
      isCreating: false
    }
  },
  computed: {
    widgetList () {
      return (this.layout)
    }
  },
  methods: {
    async addWidget (widget) {
      try {
        const request = await axios.get('/api/widget/' + widget.id, {
          headers: {
            authorization: localStorage.getItem('dashboard-token')
          }
        })
        console.log(request.data)
        this.layout.push({ x: widget.x, y: widget.y, w: 2, h: 10, static: false, i: widget.id, widgetName: widget.widgetName, serviceName: widget.serviceName, param: widget.param, refreshTime: widget.refreshTime, data: request.data })
      } catch (error) {
        console.log(error)
      }
    },
    getXYPos () {
      if (this.layout.length === 1) { return ({ x: 0, y: 0 }) } else if (this.layout.at(-1).x === 10) {
        return ({ x: 0, y: this.layout.at(-1).y })
      } else {
        return ({ x: this.layout.at(-1).x + 2, y: 0 })
      }
    },
    movedEvent: async function (id, newX, newY) {
      try {
        await axios.put('/api/widget/' + id, {
          x: newX,
          y: newY
        }, { headers: { authorization: localStorage.getItem('dashboard-token') } })
      } catch (error) {
        console.log(error)
      }
    },
    async createWidget () {
      this.$modal.show('widget')
    }
  },
  async mounted () {
    const loader = this.$loading.show()
    try {
      const requestUser = await axios.get('/api/user', {
        headers: {
          authorization: localStorage.getItem('dashboard-token')
        }
      })
      this.name = requestUser.data.username
      const request = await axios.get('/api/service', {
        headers: {
          authorization: localStorage.getItem('dashboard-token')
        }
      })
      this.$store.commit('updateServices', request.data)
      this.services = request.data
    } catch (error) {
      if (error.response && (error.response.status === 403 || error.response.status > 400)) {
        this.$root.$emit('tokenChanged', null)
        localStorage.removeItem('dashboard-token')
        this.$router.push({ path: 'login' })
      } else {
        this.$toast.error({
          type: 'error',
          message: 'An error occured while retrieving the services.'
        })
      }
    }
    try {
      const request = await axios.get('/api/widget', {
        headers: {
          authorization: localStorage.getItem('dashboard-token')
        }
      })
      for (const widget of request.data) {
        this.addWidget(widget)
      }
    } catch (error) {
      console.log(error)
    }
    await this.$root.$on('widgetCreated', async (widget) => {
      try {
        this.isCreating = true
        const { x, y } = this.getXYPos()
        const request = await axios.post('/api/widget', {
          serviceName: widget.serviceName,
          widgetName: widget.widgetName,
          param: widget.param,
          x,
          y
        }, { headers: { authorization: localStorage.getItem('dashboard-token') } })
        this.isCreating = false
        this.addWidget(request.data)
      } catch (error) {
        console.log(error)
        this.isCreating = false
      }
    })
    await this.$root.$on('deleteWidget', async (id) => {
      try {
        await axios.delete('/api/widget/' + id, {
          headers: {
            authorization: localStorage.getItem('dashboard-token')
          }
        })
        this.layout = this.layout.filter(item => item.i !== id)
      } catch (error) {
        console.log(error)
      }
    })
    loader.hide()
  }
}
</script>

<style scoped lang="scss">
.vue-grid-item:not(.vue-grid-placeholder) {
  box-shadow: rgba(0, 0, 0, 0.35) 0px 5px 15px;
  background: white;
}

.vue-grid-item {
  background: white;
  overflow-x: hidden !important;
  overflow-y: visible !important;
}

.cryptoWiget {
  background-color: rgb(251, 176, 52) !important;
  background-image: linear-gradient(315deg, rgb(251, 176, 52) 0%, rgb(234, 218, 116) 74%) !important;
  color: white !important;
  border-radius: 25px !important;
}

.timeWidget {
  background-color: #d3d3d3 !important;
  background-image: linear-gradient(315deg, #d3d3d3 0%, #7b8384 74%) !important;
  color: white !important;
  border-radius: 25px !important;
}

.dashboardWidget {
  border-radius: 20px !important;
  background-color: #045de9 !important;
  background-image: linear-gradient(315deg, #045de9 0%, #52c1ec 74%) !important;
}

.twitchWidget {
  background-color: #a4508b !important;
  background-image: linear-gradient(326deg, #a4508b 0%, #5f0a87 74%) !important;
  color: white !important;
  border-radius: 20px !important;
}

.weatherWidget {
  background-color: #6a93cb !important;
  background-image: linear-gradient(315deg, #6a93cb 0%, #a4bfef 74%) !important;
  color: white !important;
  border-radius: 20px !important;
}

.leagueWidget {
  background-color: #53aa75 !important;
  background-image: linear-gradient(315deg, #3e5e30 0%, #53aa75 74%) !important;
  border-radius: 25px !important;
  color: white !important;
}

.vue-grid-item .resizing {
    opacity: 0.9;
}
.vue-grid-item .static {
    background: #cce;
}
.vue-grid-item .text {
    text-align: center;
    margin: auto;
}
.vue-grid-item .no-drag {
    height: 100%;
    width: 100%;
}

.vue-grid-item .minMax {
    font-size: 12px;
}
.vue-grid-item .add {
    cursor: pointer;
}
.vue-draggable-handle {
    position: absolute;
    width: 20px;
    height: 20px;
    top: 0;
    left: 0;
    background: url("data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='10' height='10'><circle cx='5' cy='5' r='5' fill='#999999'/></svg>") no-repeat;
    background-position: bottom right;
    padding: 0 8px 8px 0;
    background-repeat: no-repeat;
    background-origin: content-box;
    box-sizing: border-box;
    cursor: pointer;
}

.columns {
    -moz-columns: 120px;
    -webkit-columns: 120px;
    columns: 120px;
}

</style>
