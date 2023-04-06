<template>
    <section class="hero is-fullheight-with-navbar is-default is-bold">
        <div class="hero-body">
            <div class="container has-text-centered">
                <div class="columns is-vcentered">
                    <div class="column is-5">
                        <figure class="image is-4by4">
                            <img src="https://f.hellowork.com/blogdumoderateur/2017/03/datadeck-dashboard-612x383.png" alt="Description">
                        </figure>
                    </div>
                    <div class="column is-6 is-offset-1">
                        <h1 class="title is-2">
                            Dashboard EPITECH 2021
                        </h1>
                        <h2 class="subtitle is-4">
                            {{ $t('Home.welcome') }}
                        </h2>
                        <br>
                        <p class="has-text-centered mb-6">
                            <a class="button is-medium is-info is-outlined" @click="showText">
                            {{ $t('Home.learnMore') }}
                            </a>
                        </p>
                        <div class="container" style="font-weight:500;font-size:1rem">
                            <transition name="slide-fade">
                                <div v-if="showing">
                                    <div> {{ $t('Home.textOne') }} </div>
                                    <div> {{ $t('Home.textTwo') }} </div>
                                </div>
                            </transition>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <div class="hero-foot">
            <div class="container">
                <div class="tabs is-centered">
                    <ul>
                        <li><a class="has-text-gray-darker" style="font-weight:700"> @Made by jean-baptiste.roesch@epitech.eu and florian.golling@epitech.eu </a></li>
                    </ul>
                </div>
            </div>
        </div>
    </section>
</template>

<script>

export default {
  name: 'Home',
  components: {
  },
  data () {
    return {
      showing: false
    }
  },
  methods: {
    showText () {
      this.showing = !this.showing
    }
  }
}
</script>

<style scoped lang="scss">

.slide-fade-enter-active {
  transition: all .5s ease;
}
.slide-fade-leave-active {
  transition: all .5s cubic-bezier(1.0, 0.5, 0.8, 1.0);
}
.slide-fade-enter, .slide-fade-leave-to {
  transform: translateX(10px);
  opacity: 0;
}

</style>
