import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    services: [],
    token: ''
  },
  mutations: {
    updateServices (state, services) {
      state.services = services
    }
  },
  actions: {
  },
  modules: {
  },
  getters: {
    getServices: state => {
      return state.services
    },
    getWidgets: state => {
      const widgets = []
      for (const service of state.services) {
        for (const widget of service.widgets) {
          widgets.push(widget)
        }
      }
      return (widgets)
    }
  }
})
