import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import Buefy from 'buefy'
import VModal from 'vue-js-modal'
import VueToast from 'vue-toast-notification'
import Loading from 'vue-loading-overlay'
import i18n from './i18n'
import vueDebounce from 'vue-debounce'
import 'vue-toast-notification/dist/theme-sugar.css'
import 'vue-loading-overlay/dist/vue-loading.css'
import 'buefy/dist/buefy.css'

Vue.config.productionTip = false
Vue.use(Buefy)
Vue.use(VueToast)
Vue.use(VModal)
Vue.use(Loading)
Vue.use(vueDebounce)

new Vue({
  router,
  store,
  i18n,
  render: h => h(App)
}).$mount('#app')
