<template>
    <section>
        <b-steps class="mt-5"
            v-model="activeStep"
            :animated="isAnimated"
            :rounded="isRounded"
            :has-navigation="hasNavigation"
            :label-position="labelPosition"
            :mobile-mode="null">
            <b-step-item step="1" label="Service" type="is-info">
                <h1 class="mt-5 subtitle has-text-centered has-text-black">Choose your widget's service</h1>
                <div class="buttons has-text-centered is-centered mt-3">
                    <button v-for="item in getAllServices" v-bind:key="item.properties.name" class="button is-info is-medium" @click="serviceChosen(item.properties.name)">
                        {{ item.properties.name }}
                    </button>
                </div>
            </b-step-item>

            <b-step-item step="2" label="Widget" type="is-info">
                <h1 class="mt-5 subtitle has-text-centered has-text-black">Choose your widget's type</h1>
                <div class="buttons has-text-centered is-centered">
                    <button class="button is-medium is-info" v-for="item in actualService.widgets" v-bind:key="item.properties.name" @click="widgetChosen(item.properties.name)">
                        {{ item.properties.name }}
                    </button>
                </div>
            </b-step-item>

            <b-step-item step="3" class="has-text-centered" type="is-info" label="Finish" disabled>
                <h1 class="mt-5 subtitle has-text-centered has-text-black">Choose your widget's parameter</h1>
                <b-field :label="actualWidget.properties.params.name">
                    <b-input v-model="paramater">
                    </b-input>
                </b-field>
                <div class="buttons has-text-centered is-centered mt-3 pb-6">
                    <button class="button is-small is-rounded is-info" @click="applyWidget()">
                        Apply
                    </button>
                </div>
            </b-step-item>
        </b-steps>
    </section>
</template>

<script>
export default {
  data () {
    return {
      activeStep: 0,
      isAnimated: true,
      isRounded: true,
      hasNavigation: false,
      customNavigation: false,
      labelPosition: 'bottom',
      serviceID: '',
      widgetID: '',
      paramater: '',
      actualService: {},
      actualWidget: {
        properties: {
          params: {
            name: ''
          }
        }
      }
    }
  },
  methods: {
    async serviceChosen (id) {
      this.serviceID = id
      this.actualService = this.$store.getters.getServices.find(element => element.properties.name === this.serviceID)
      this.activeStep++
    },
    async widgetChosen (id) {
      this.actualWidget = this.$store.getters.getServices.find(element => element.properties.name === this.serviceID).widgets.find(el => el.properties.name === id)
      this.widgetID = id
      this.activeStep++
    },
    async applyWidget () {
      await this.$root.$emit('widgetCreated', { widgetName: this.widgetID, serviceName: this.serviceID, param: this.paramater })
      this.$modal.hide('widget')
    }
  },
  computed: {
    getAllServices () {
      return this.$store.getters.getServices
    }
  }
}
</script>
