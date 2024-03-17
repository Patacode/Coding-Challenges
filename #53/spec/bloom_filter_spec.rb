# frozen_string_literal: true

require 'bloom_filter'

RSpec.configure do |config|
  config.before(:context, target_cls: BloomFilter) do
    @bloom_filter = BloomFilter.new(100, epsilon: 0.1)
  end

  config.before(:example, fresh_data: true) do
    @fresh_bloom_filter = BloomFilter.new(100, epsilon: 0.1)
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
        '24626253872746549507674400062589758628174837044040904167467687208892' \
        '42827190790252800148428507603150249593321553920'.to_i
      )
    end
  end

  describe '#<<', fresh_data: true do
    it 'adds the provided element to the bloom filter (acts as #add)' do
      @fresh_bloom_filter << 'hello'

      expect(@fresh_bloom_filter.to_i).to eq(
        '24626253872746549507674400062589758628174837044040904167467687208892' \
        '42827190790252800148428507603150249593321553920'.to_i
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

  describe '::new', fresh_data: true do
    after(:example) do
      FileUtils.rm_f('result.bf')
    end

    it 'loads the bloom filter from the provided filepath' do
      bf = BloomFilter.new('data/valid_result_sample.bf')

      expect(bf.version).to eq(1)
      expect(bf.hash_function_count).to eq(7)
      expect(bf.size).to eq(959)
      expect(bf.to_i).to eq(
        '4470899740107962273404506183803811265995867971410579331409297915010' \
        '7868870456392257967418147447718593730757326681478565165724423315524' \
        '0148440272805764320212458691950827065875291323364753820380255734511' \
        '3670969971847558793188109897451545575757016731115973044856104404538' \
        '98156122300493540022'.to_i
      )
    end

    it 'raises an exception if the provided file is not of the right type' do
      load_bf_from_file = lambda do
        BloomFilter.new('data/invalid_result_sample.bf')
      end

      expect { load_bf_from_file.call }.to raise_error(ArgumentError)
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
        "CCBF\x00\x01\x00\x04\x00\x00\x01\xE0\x00\x00\x00\x01\x00\x00@\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\x04\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00@\x00\x00\x10\x00\x00\x11"
      )
    end

    it 'increases the version of the saved file when first loaded from file' do
      @fresh_bloom_filter << 'hello'
      @fresh_bloom_filter << 'world'

      @fresh_bloom_filter.save_to_file('result')

      bf = BloomFilter.new('result.bf')
      bf.save_to_file('result')
      bf = BloomFilter.new('result.bf')

      expect(bf.version).to eq(2)
    end

    it 'increases the version of the saved file when saved multiple times' do
      @fresh_bloom_filter << 'hello'
      @fresh_bloom_filter << 'world'

      @fresh_bloom_filter.save_to_file('result')
      @fresh_bloom_filter.save_to_file('result')

      bf = BloomFilter.new('result.bf')

      expect(bf.version).to eq(2)
    end

    it 'increases the version of the saved file according to given version' do
      bf = BloomFilter.new(100, version: 3)
      bf.save_to_file('result')

      bf = BloomFilter.new('result.bf')

      expect(bf.version).to eq(4)
    end
  end
end
