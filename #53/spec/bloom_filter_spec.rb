# frozen_string_literal: true

require 'bloom_filter'

RSpec.configure do |config|
  config.before(:context, target_cls: BloomFilter) do
    @bloom_filter = BloomFilter.new('data/dict_sample.txt', epsilon: 0.1)
  end

  config.before(:example, fresh_data: true) do
    @fresh_bloom_filter = BloomFilter.new('data/dict_sample.txt', epsilon: 0.1)
  end
end

RSpec.describe BloomFilter, target_cls: BloomFilter do
  describe '#size' do
    it 'returns the number of bits used by the bloom filter' do
      expect(@bloom_filter.size).to eq(480)
    end
  end

  describe '#hash_function_count' do
    it 'returns the number of hash functions used by the bloom filter' do
      expect(@bloom_filter.hash_function_count).to eq(4)
    end
  end

  describe '#to_i' do
    it 'returns the bit array value as integer used by the bloom filter' do
      expect(@bloom_filter.to_i).to eq(0)
    end
  end

  describe '#add', fresh_data: true do
    it 'adds nothing to the bloom filter if provided element is empty' do
      @fresh_bloom_filter.add('')

      expect(@fresh_bloom_filter.to_i).to eq(0)
    end

    it 'adds the provided element to the bloom filter' do
      @fresh_bloom_filter.add('hello')

      expect(@fresh_bloom_filter.to_i).to eq(
        '93035356796483609931588911771490023651737459904439442274193985641736' \
        '20714954060637678119199869280908380424611367960883167766478883651584' \
        '0'.to_i
      )
    end
  end

  describe '#<<', fresh_data: true do
    it 'adds the provided element to the bloom filter (acts as #add)' do
      @fresh_bloom_filter << 'hello'

      expect(@fresh_bloom_filter.to_i).to eq(
        '93035356796483609931588911771490023651737459904439442274193985641736' \
        '20714954060637678119199869280908380424611367960883167766478883651584' \
        '0'.to_i
      )
    end
  end

  describe '#include?', fresh_data: true do
    before(:example) do
      @fresh_bloom_filter << 'hello'
    end

    it 'returns true if the provided element is most likely in the set' do
      expect(@fresh_bloom_filter.include?('hello')).to be(true)
    end

    it 'returns false if the provided element is most likely not in the set' do
      expect(@fresh_bloom_filter.include?('zebra')).to be(false)
    end
  end

  describe '#===', fresh_data: true do
    before(:example) do
      @fresh_bloom_filter << 'hello'
    end

    it(
      'returns true if the provided element is most likely in the set (acts ' \
      'as #include?)'
    ) do
      expect(@fresh_bloom_filter === 'hello').to be(true)
    end

    it(
      'returns false if the provided element is most likely not in the set ' \
      '(acts as #include?)'
    ) do
      expect(@fresh_bloom_filter === 'zebra').to be(false)
    end
  end

  describe '#save_to_file', fresh_data: true do
    after(:example) do
      FileUtils.rm_f('result.bf')
    end

    it 'saves the internal bit array of bloom filter in a file on disk' do
      @fresh_bloom_filter << 'hello'
      @fresh_bloom_filter << 'world'

      @fresh_bloom_filter.save_to_file('result')

      expect(File).to exist('result.bf')
      expect(File.read('result.bf')).to eq(
        "\x00\x00\x00\x80\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00 \x00 \x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\b\x00\x00\x88\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00"
      )
    end
  end
end
